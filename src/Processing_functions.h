#include "Triangle.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
 
#include "Triangle.h"
#ifndef PROCESSING_FUNCTIONS_H
#define PROCESSING_FUNCTIONS_H
using namespace std;
//takes in the triangle vector;
double get_Scale(double x_min, double x_max, double y_min,double y_max,double width, double height ){
	//calculate scale by dividing height and width by the height and width of the mesh to get scale
		double mesh_height = y_max - y_min;
		double mesh_width = x_max - x_min;
        double scale_x = width / mesh_width;
		double scale_y = height / mesh_height;
		return (scale_x < scale_y) ? scale_x : scale_y;

};

pair<double,double> get_offset(double x_min, double x_max, double y_min,double y_max,double width, double height ){

    //calculates the offset
		double YmidMesh =  0.5 * (y_max + y_min);
		double XmidMesh = 0.5 * (x_max + x_min);

        double scale = get_Scale( x_min,  x_max,  y_min, y_max, width,  height );


       return  make_pair((0.5 * width) - (scale * XmidMesh),(0.5 * height ) - (scale * YmidMesh));

}
//only converts a single point from mesh to image
pair<double,double> point_Mesh_to_image(double x,double y,double x_min, double x_max, double y_min,double y_max,double width, double height){
		

		double s = get_Scale(x_min, x_max, y_min, y_max, width, height);
		pair<double,double> offset = get_offset(x_min,  x_max,  y_min, y_max, width,  height );

		return make_pair(s*x+offset.first,s*y + offset.second);

};
	
double vect_max(vector<double>& input_vect){
		
		return *(max_element(input_vect.begin() , input_vect.end()));
};
double vect_min(vector<double>& input_vect){
		return *(min_element(input_vect.begin(), input_vect.end()));
}

	//function that convverts the triangle vertexes from mesh to image coords
void Tri_Mesh_to_image( vector<shared_ptr<Triangle>>& Triangle_Vector, double x_min, double x_max, double y_min,double y_max,double width, double height ){
        //gets min and max for x and y of who entire mesh
	

    double S = get_Scale(x_min,x_max,y_min,y_max,width,height);
    pair<double,double> offset  = get_offset(x_min,x_max,y_min,y_max,width,height);     
        //loop through all triangles and update all the x and y values to image coords
        for(size_t n = 0; n < Triangle_Vector.size(); n++){

                Triangle_Vector.at(n)->get_v1().x = S* Triangle_Vector.at(n)->get_v1().x + offset.first;
                Triangle_Vector.at(n)->get_v1().y = S* Triangle_Vector.at(n)->get_v1().y + offset.second;
                
                Triangle_Vector.at(n)->get_v2().x = S* Triangle_Vector.at(n)->get_v2().x + offset.first;
                Triangle_Vector.at(n)->get_v2().y = S* Triangle_Vector.at(n)->get_v2().y + offset.second;

                Triangle_Vector.at(n)->get_v3().x = S* Triangle_Vector.at(n)->get_v3().x + offset.first;
                Triangle_Vector.at(n)->get_v3().y = S* Triangle_Vector.at(n)->get_v3().y + offset.second;

            
        }

}

	//returns bool that determines if a point is in or outside the triangle 
	bool Baycentric_coord_check(double Px, double Py, double Ax , double Ay , double Bx, double By, double Cx, double Cy ) {
		//calculates the baycentric coordinates
		double total_Area = 0.5 * ((Bx - Ax) * ( Cy - Ay ) - (Cx - Ax) * (By-Ay) ) ;
		double Area_A = (0.5 * ((Bx - Px) * (Cy - Py) - (Cx - Px) * (By - Py))) / total_Area ;
		double Area_B = (0.5 * ((Cx - Px) * (Ay - Py) - (Ax - Px) * (Cy - Py))) / total_Area;
		double Area_C = (0.5 * ((Ax - Px) * (By - Py) - (Bx - Px) * (Ay - Py))) / total_Area;
			//makes sure point is inside the Triangle
		if (( Area_A >= -0.00000000000000000001 && Area_A <= 1) && ( Area_B >= -0.000000000000000001 && Area_B <= 1 ) && ( Area_C >= -0.000000000000000001 && Area_C <= 1)){
			return true;
		}
		return false;

		};
	//stores Area of the Baycentric coords  in a pair of ( a double and a pair of doubles)
  pair< double,pair<double, double>> Baycentric_Coord_area(double Px, double Py, double Ax , double Ay , double Bx, double By, double Cx, double Cy){

		double total_Area = 0.5 * ((Bx - Ax) * ( Cy - Ay ) - (Cx - Ax) * (By-Ay) ) ;
		double Area_A = (0.5 * ((Bx - Px) * (Cy - Py) - (Cx - Px) * (By - Py))) / total_Area ;
		double Area_B = (0.5 * ((Cx - Px) * (Ay - Py) - (Ax - Px) * (Cy - Py))) / total_Area;
		double Area_C = (0.5 * ((Ax - Px) * (By - Py) - (Bx - Px) * (Ay - Py))) / total_Area;
		//sets values of rgb relative to the positions of the corners  however 
		


		pair< double, pair<double, double>> Areas =  make_pair(Area_A, make_pair(Area_B,Area_C));


		return  Areas;

    };


	double simple_light_calc(vector<double>& norm_vect){
		double scalar;
		vector<double> light_vect = {0.57735026919,0.57735026919,0.57735026919};


		scalar = max({light_vect.at(0) * norm_vect.at(0) + light_vect.at(1) * norm_vect.at(1)   + light_vect.at(2) * norm_vect.at(2), 0.00});
		
		

		return scalar;
	};

	//will get the ratio of point to final and intial to point and return it in a pair conatining the values in the stated order
	pair <double,double> Baycentric_linear_interpolation( double point, double initial,double final){
	
		pair<double,double> ratio;
		//will find the linear baycentric interpolation
			double total_dist =  final - initial;
			double initial_ratio = (final - point) / total_dist;
			double final_ratio = (point - initial)/total_dist;
		ratio = make_pair(initial_ratio,final_ratio);
		return ratio;

	 };

	//will take list of vectors  rotate along y-axis by 45 degrees using matrix mult
 void y_rotate45(vector<float>& input){
		//hardcoded since only will need to do a 45 degree along y-axis
		double x;
		double z;
	for (unsigned int i = 0; i < input.size(); i+=3){
		
		x =  (0.7071*input.at(i) +  0.7071*input.at(i+2));
		//y position remains the same so don't update it

		z = (-0.7071 * input.at(i) + 0.7071*input.at(i+2)) ;

		input.at(i) = x;
		input.at(i+2) = z;
	}
		
 };
//checks if color is outside the range 
	void Color_check(int& input_color){
		
	if (input_color > 255) {
		input_color = 255;
	}
	else if (input_color < 0) {
	 input_color = 0;
	}

	}

//checks if the file type is a png or jpeg 
int File_type_check(string input){
	if(input.size() < 4){
		throw std::runtime_error("not enough characters for output file name must have a file name and identifier i.e  bunny.png  ");
	}
	else if((input.find(".png",input.size() - 5  ) == input.npos )&& (input.find(".jpeg",input.size() -5)  == input.npos) && (input.find(".jpg", input.size()-5)  == input.npos)){
		throw std::runtime_error("Please use png or even jpeg for the file extension and make sure to include \'.\', ex: \"image.png\"");
	}
	else{
		return 0;
	}
};

#endif