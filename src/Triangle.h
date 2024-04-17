/*
Includes the Triangle class along with it's functions 

*/
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "Triangle.h"
using namespace std;
//holds vertex data information(coordinates)
		struct Vertex
		{
			//position values
			double x;
			double y;
			double z;
			
			vector<double> Norm;
			

			//color values for each 
			double r;
			double b;
			double g;
		};

//class used to store triangle data such as meshes, max and min coordinate of each triangle
	class Triangle
	{

	private:
		
		Vertex v_1;
		Vertex v_2;
		Vertex v_3;

		


	public:
		//sets up the vertices and chooses -1 for position if not specified;
		Triangle(double x1 = -1, double y1 = -1, double z1 = -1, double x2 = -1, double y2 = -1, double z2 = -1, double  x3 = -1, double y3 = -1, double z3 = -1) {
			v_1.x = x1;
			v_1.y = y1;
			v_1.z = z1;
			v_1.r = 0;
			v_1.g = 0;
			v_1.b = 0;
			

			v_2.x = x2;
			v_2.y = y2;
			v_2.z = z2;
			v_2.r = 0;
			v_2.g = 0;
			v_2.b = 0;
			

			v_3.x = x3;
			v_3.y = y3;
			v_3.z = z3;
			v_3.r = 0;
			v_3.g = 0;
			v_3.b = 0;
			

		};

    
		//color values for each triangle
		double r = 0;
		double g = 0;
		double b = 0;

		//getters if each vertex is needed for operations
		Vertex& get_v1() {
			return v_1;
		};
		Vertex& get_v2() {
			return v_2;
		};
		Vertex& get_v3() {
			return v_3;
		};
	
		
		//returns min&max of the x,y,z of a triangle
		const double get_xmin() {
			
			return min({ v_1.x, v_2.x,v_3.x });
			

			
		};
	const double get_ymin() {
		
				return min({ v_1.y, v_2.y,v_3.y });
			
			
		};
		double get_zmin() {
			return min({ v_1.z, v_2.z,v_3.z });
		};
		double get_xmax() {
			return max({ v_1.x, v_2.x,v_3.x });
		};
		double get_ymax() {
			return max({ v_1.y, v_2.y,v_3.y });
		};
		double get_zmax() {
			return max({ v_1.z, v_2.z,v_3.z });
		};
	
	
    };

    
	class Z_buffer
	{
	private:
	int z_height;
	int z_width;
	//make vector of shared vector ptrs 
	vector<shared_ptr<vector<double>>> z_values;
	
		
	public:
		// 2x2 dynamic 'smart' vector
	
	//intializes a 2x2 smart vector
	Z_buffer(int& height,int& width): z_height(height),z_width(width) {
			z_values.resize(z_height,nullptr);
			for (int i = 0; i < z_height; i++){
				z_values.at(i) = make_shared<vector<double>>(z_width, -999);
				}
			
			
			
	};

	
	bool add_z_value( double& input_z,const int& x,const int& y){
		if ( input_z > (z_values.at(y)->at(x)) ){
			//adds new z_coord and returns true so the pixel can be written
			(this->z_values.at(y)->at(x)) = std::move(input_z);

			return true;
		}
		else{
			return false;
		}
	};
	double& get_zvalue(int x,int y){
		return (z_values.at(y)->at(x));
	};
	int size(){
		return z_width*z_height;
	};
	int width(){
		return z_width;
	};
	int height(){
		return z_height;
	};
	};
	

	
	
	
	
	


#endif



