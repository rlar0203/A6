
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
    double max_dimension = std::max(height,width);

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
    for (int i = 0; i < max_dimension; i++)
    {
       for(int j = 0; j < max_dimension; j++){
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
        Object(vec3 point,vec3 kd, vec3 ka, vec3 ks, double s): point(point) {};
        virtual ~Object() {};
    };
    

    


    class Ellipsoid : public Object
    {
        private:
        //assumes radius are equal when working in local space so they will be the same 
        double radius = 1.00;
        
        //transformation matrix  goint from local to world
        mat4 E(1.0); //automatically identity 

        public:
        //assumes no scale and a rotation of zero around the xy axis 
        Ellipsoid( vec3 point, vec3 kd, vec3 ka, vec3 ks, double s, vec3 SCALE = vec3(1.00,1.00,1.00), vec3 Rotation_axis = vec3(1,1,0), double rotation_angle = 0 ): Object(point,kd,ka,ks,s){
            //applies the transformations and stores them in E matrix
            E = scale(E, SCALE);
            E = rotate(E,rotation_angle,Rotation_axis);

        }

        vector<vec3> single_raytrace(vec3 Ray_dir, vec3 Ray_origin){
            //transforms the ray vectors into local space (if it is an identiy matrix will remain the same)
            vec3 T_raydir = (inverse(E) * vec4(Ray_dir, 0.0)).xyz;
            vec3 T_rayorig = (inverse(E) * vec4(Ray_origin, 0.0)).xyz;

            vector<vec3> Results(3,vec3(0.0,0.0,0.0));

        //storing values to be used in calculating t 
        double a = dot(T_raydir , T_rayorig);
        double b = 2* dot(v,(T_rayorig - point));
        double d = (b*b) - (4*a*());


        // TODO FINISH ELLIPSOID/SPHERE RAY TRACER THEN DO THE PHONG FUNCTION 
        // - finsih calculations in ray tracer 
        // - 
        if()



            return Results;
        }


    }

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
        vector<vec3> single_raytrace( vec3 Ray_dir, vec3 Ray_origin){
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

    

    
    
    
#endif
