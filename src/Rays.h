
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
    public:
        virtual ~Object() {};

        virtual double ray_trace() const = 0;
    };
    

    


    class Ellipsoid : private Object
    {
        


    }

    class plane : private Object
    {
    private:
        /* data */
    public:
        plane(/* args */);
        ~plane();
    };
    
    plane::plane(/* args */)
    {
    }
    

    
    
    
#endif
