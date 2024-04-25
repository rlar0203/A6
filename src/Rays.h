
#ifndef RAYS_H
#define RAYS_H

#include <iostream>
#include <string>

#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;
using namespace glm;

//create function that generates rays given a camera 
vector<vec3> Ray_gen(vec3 camera,vec3 plane_pos,int height,int width){
//uses max_dimension to perserve the 1.0 aspect ratio
    int max_dimension = std::max(height,width);
  
//makes empty vectors for all the possible rays avaialble 
vector<vec3> Rays (max_dimension*max_dimension, vec3(0.0,0.0,0.0));
       
    //calculates 45 degrees in radians
  double   FOV_y = M_PI*((double)45/(double)180);
    
    //calculates the distance of the plane to the camera 
    double plane_dist = glm::distance(camera,plane_pos);

    //gets the dimension of the grid side 
   double  grid_size = 2.0 *( plane_dist * tan(FOV_y/2));


    //gets the pixel dimensions 
   double pixel_size =  grid_size / std::max(height,width); 

//starting at 0,0 being the bottom left corner so 
    for (int i = 0; i < (int)max_dimension; i++)
    {
       for(int j = 0; j < (int)max_dimension; j++){
        //gets the x position starting at the left and then going right 
        Rays.at(max_dimension*i +j).x = pixel_size * ( j - (max_dimension/2.0) + 0.5) ;


        //makes this negative so the starting point is now the top left 
        Rays.at(max_dimension*i +j).y = -pixel_size * (i - (max_dimension/2.0) + 0.5) ;

        //for now will just set it to the difference to minus the z components
        Rays.at(max_dimension*i +j).z = (plane_pos.z - camera.z);



         //normalizes each ray to get the unit direction
       Rays.at(max_dimension*i +j) = normalize(Rays.at(max_dimension*i +j));
       }      
    }
    

    //returns the generated rays 
    return Rays;

}

//stores all the shape values along with hit information in the struct for use in phong shader
struct RESULTS{
    vec3 hit_pos;
    vec3 hit_norm;
    double distance;
        vec3 kd;
        vec3 ks;
        vec3 ka;
        double s;
};


//sets up the parent class which has the children classes inheriting from the parent 
    class Object
    {
    protected:
        vec3 point;
        //color values for the object

        
    public:        
        vec3 kd;
        vec3 ks;
        vec3 ka;
        double s;
    //basic constructor for the object so we can all the constructor inside the subshape constructors
        Object(vec3 point,vec3 kd, vec3 ka, vec3 ks, double s): point(point) {
                this->kd = kd;
                this->ks = ks;
                this->ka = ka;
                this->s = s;
        };
        virtual ~Object() {};
        //basic function to be overloaded by children classes
        virtual vector<vec3> single_raytrace(vec3 Ray_dir, vec3 Ray_origin){ printf("if you see this error has occured and this isn't being over loaded");
            exit(1);
            vector<vec3> empty_vector(1);
            return empty_vector;
         };
    };
    

    

            //ellipsoid/sphere object 
    class Ellipsoid : public Object
    {
        private:
        //assumes radius are equal when working in local space so they will be the same 
        double radius = 1.0;
        
        //transformation matrix  goint from local to world
        mat4 E = mat4(1.0); //automatically identity 

        public:
        //assumes no scale and a rotation of zero around the xy axis 
        Ellipsoid( vec3 point, vec3 kd, vec3 ka, vec3 ks, double s,vec3 TRANSLATION = vec3(0.0,0.0,0.0) ,vec3 SCALE = vec3(1.0,1.0,1.0), vec3 Rotation_axis = vec3(0.0,1.0,0.0), float rotation_angle = 0.0 ): Object(point,kd,ka,ks,s){
            //applies the transformations and stores them in E matrix
            E = translate(E,TRANSLATION) * glm::rotate(mat4(1.0),rotation_angle,Rotation_axis)*scale(E, SCALE);

        }
        //returns -1,-1,-1 if a no hit else it will return the closests hit with a positive distance to the camera 
        vector<vec3> single_raytrace(vec3 Ray_dir, vec3 Ray_origin) override {
            //transforms the ray vectors into local space (if it is an identiy matrix will remain the same)
            vec3 T_raydir = vec3((inverse(E) * vec4(Ray_dir, 0.0))); //uses 0 for homo coord
            vec3 T_rayorig = vec3((inverse(E) * vec4(Ray_origin, 1.0))); //uses 1 for homo coord

            vector<vec3> Results(3,vec3(0.0,0.0,0.0));


        //storing values to be used in calculating if a hit occurs or not and to make it easier to understand
        double a = dot(T_raydir , T_raydir);
        double b = 2* dot(T_raydir,(T_rayorig - point));
        double c = dot((T_rayorig - point),(T_rayorig - point)) -  static_cast<float>(radius);
        double d = (b*b) - (4*a*c);


        //handles d being negative (NO HIT)
        if( d < -0.0001){
            //returns an vec3 with empty dir and normal and a vec3 full of negative distances to indicate a miss
            Results.at(0) = vec3(-1.0,-1.0,-1.0);

            //don't have to worry about transforming since we missed and so it isn't needed 
            return Results;

        }
        //handles d being greater than 0 or value near 0 due to accuracy issues   (2 HITS)
        else if( d > 0.0001){
            //calculates the  distance of the two hits and uses the smallest one in the calculations

            double t1 = (-b + sqrt(d))/ (2*a);
            double t2 = ((-b - sqrt(d))/ (2*a));


            //choses lowest distance (positive)
            Results.at(0).x = (t1 < t2 && t1 >= 0) ?  t1:  t2;

            //using lowest distance calculates HIT POSTION
            Results.at(1) = T_rayorig + Results.at(0).x * T_raydir;


            //calculates the normal 
            Results.at(2) = (Results.at(1) - point)/ static_cast<float>(radius);
        }
        //handles condition is near 0  (1 HIT)
        else{
           
            //since d = 0 uses simplified quadratic formula
             Results.at(0).x = -b / (2*a);

            //using lowest distance calculates HIT POSTION
            Results.at(1) = T_rayorig + Results.at(0).x * T_raydir;


            //calculates the normal 
            Results.at(2) = (Results.at(1) - point) /  static_cast<float>(radius);

            
        }
         //transforms hit pos and hit norm back to world coords and rederives the distance in world coords
    
        Results.at(1) = vec3((E * vec4(Results.at(1), 1.0)));

           
        //renormalizes just in case of length no longer being 1 for normal.
        Results.at(2) =   vec3(E * vec4(Results.at(2), 0.0));
        Results.at(2) = normalize(Results.at(2));


        //gets the distance from the world coord ray hit postiion and direction
        Results.at(0).x =  glm::length(Results.at(1) - Ray_origin);

        //gets negative of the value if the dot product of difference of (hit point and ray origin point) and ray direction
        if( dot(Ray_dir,Results.at(1) - Ray_origin) < 0 ){
            Results.at(0).x = -(Results.at(0).x);
        }

            return Results;
        }


    };

    class plane : public Object
    {
    private:
    vec3 normal;
    public:
    // creates plane and initalizes values in parent 
        plane(vec3 normal, vec3 point, vec3 kd, vec3 ka, vec3 ks, double s): Object(point,kd,ka,ks,s){
            this->normal = normal;
        };
        //does ray_tracing for a singluar ray and returns the hit position, hit normal and the hit distance 
        vector<vec3> single_raytrace( vec3 Ray_dir, vec3 Ray_origin) override {
        //results which include 1 distance value stored in x position in a vec3 and  two vec3 for point hit and hit normal
        vector<vec3> Results(3,vec3(0.0,0.0,0.0));

        //checks if the ray is parrallel to plane to avoid trying to divide by zero just in case 
        double angle_ray_plane = dot(normal,Ray_dir);

        if(angle_ray_plane > 0.00000000000001 || angle_ray_plane < -0.00000000000001){
            //calculates t value
            Results.at(0).x = (dot(normal, point) - dot(normal,Ray_origin) ) / dot(normal,Ray_dir);

            //calculates the hit position
            Results.at(1) = Ray_origin + (Ray_dir * Results.at(0).x);

            //since every point on the plane has the same normal so hit normal = plane normal
            Results.at(2) = normal;
        }
        //returns all negative distance vals in vec3 meaning ray can't hit plane
        else{
            Results.at(0) = vec3(-1,-1,-1);
        }


            return Results;
        };
        
    };



//raytracing hit funciton (will return the object material properties associated with the smallest positive distance from ray origin to hit postion) and takes in returnvalues as an arg which will store the postion values 
 bool Ray_Hit(vec3 ray_dir,vec3 ray_origin, vector<Object*>& shapes, RESULTS& phong_info ){
    //sets shape index to negative 1 to indicate we haven't hit anything
    double min_dist;
    bool hit = 0;

    vector<vec3> return_values(3);
    int shape_index = -1;
    return_values = shapes.at(0)->single_raytrace(ray_dir, ray_origin);
    //sets to first shape to first shape distance 
    min_dist = return_values.at(0).x;

    //loops through each shape tries to find the minimum postive distance
    for (int i = 0; i < (int)shapes.size(); i++)
    {
        
        return_values = shapes.at(i)->single_raytrace(ray_dir, ray_origin);

   //only swtiches our min dist to current dist if both are postive and min > curr    or  min is a negative and the curr min is postive
     if( (min_dist >= 0 && min_dist >= return_values.at(0).x && return_values.at(0).x >= 0) || (min_dist < 0 && return_values.at(0).x > 0) ){
             min_dist = return_values.at(0).x;
            shape_index = i;
        }
        

        //value will continue to stay the same if both values are negative or  min is still less than current dist  
    }
    if(min_dist >= 0){



        phong_info.kd = shapes.at(shape_index)->kd;
        phong_info.ks = shapes.at(shape_index)->ks;
        phong_info.ka = shapes.at(shape_index)->ka;
        phong_info.s = shapes.at(shape_index)->s;

    } 
        phong_info.hit_pos = return_values.at(1);
        phong_info.hit_norm = return_values.at(2);
        phong_info.distance = min_dist;

    hit = (min_dist >= 0.0001)? 1 : 0 ;
   
    return hit;
}
 
  // colors pixels based on data given 
  
vec3 ray_color_gen(vec3 Ray,vec3 ray_origin ,vector<Object*> &objects, vector<vec3>& light_pos, vector<vec3>& light_color){

        vec3 color = vec3(0.0,0.0,0.0);
        //will be overwritten when passed into the function 
       RESULTS phong_stats;
       if( Ray_Hit(Ray,ray_origin,objects,phong_stats)){
        vec3 color = phong_stats.ka;

        printf("hit\n");
      //normalizes as a precautionary measure
        vec3 n = normalize(phong_stats.hit_norm);
         vec3 e = normalize(ray_origin - phong_stats.hit_pos);
        //calculates the phong shader using each light given
        for (size_t i = 0; i < light_pos.size(); i++)
        {
        vec3 light_dir = normalize(light_pos.at(i) - phong_stats.hit_pos);
       
        vec3 h = normalize(light_dir + e);
        float max2 = glm::max( 0.0f, dot(n,h));
        
        color += light_color.at(i) * (phong_stats.kd* glm::max(0.0f,dot(n,light_dir)) + phong_stats.ks *   pow( max2 , (float)phong_stats.s )     );

        }
        return color;
    
       }
        //will deal with shadows in here using shadow tracer
       else{
        //colors image black if not hit 
        
        color = vec3(0,0,0);
       }

       return color;
        
        
        


    }
    
    
    
    
#endif
