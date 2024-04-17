#include <iostream>
#include <string>
#include <memory>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <algorithm>
#include "Image.h"
#include "Triangle.h"
#include "Processing_functions.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char** argv)

{
	
	if (argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	else if(argc < 5){
		
			cout << "not enough command line arguments" << endl;
			return 1;
		
	}
	string meshName(argv[1]);
	string output_name(argv[2]);
		int width;
		int height;
		int task;
		//include a check which makes sure the user saves as a valid image file i.e png,jpeg
	
	try
	{
	
	width = stoi(argv[3]);
	height = stoi(argv[4]);
	task = stoi(argv[5]);
	}
	catch(...)
	{
	std::cout << " please make sure to include all command line arguments meshname, outputname,  width, height and task and that the last 3 arguments are positive integers" << endl;
	std::cout << "also, make sure that the number for width, height and task don't exceed INT MAX(2147483647)" << endl;
			return 1;
	}
try
{
	File_type_check(output_name);
}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
	return 1;
}
if(width < 0 || height < 0|| task < 0){
		cout << "Make sure you use POSITIVE integers for width, height and task" << endl;
		return 1;
	}	
	

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if (!rc) {
		cerr << errStr << endl;
		return 1;
	}
	else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
					if (!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 0]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 1]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 2]);
					}
					if (!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	
	cout << "Number of vertices: " << posBuf.size() / 3 << endl; \
	if(task == 8){
		// rotates the vectors before putting them in triangle class and processing them
		y_rotate45(norBuf);
		y_rotate45(posBuf);
	}
	shared_ptr<Image> image = make_shared<Image>(width, height);

	
	
	//used to get min and max of the entire mesh
	
	vector < double > Xpos;
	vector < double > Ypos;
	vector < double > Zpos;
	//copies values of position Buffers into 2 sperate lists so we can get the max_X and max_y for the whole mesh
	for (unsigned int i = 0; i < posBuf.size(); i += 3) {
		Xpos.push_back(posBuf.at(i));
		Ypos.push_back(posBuf.at(i + 1));
		Zpos.push_back(posBuf.at(i + 2));

	}
	double y_min = vect_min(Ypos);
	double y_max = vect_max(Ypos);
	double x_min = vect_min(Xpos);
	double x_max = vect_max(Xpos);

	//make list of Traingle smart pointers where we don't  have to worry about memory allocation
	size_t list_size = posBuf.size() / 9;

	vector<shared_ptr<Triangle>> Triangle_list(list_size);
	for (unsigned int i = 0; i < list_size; i++) {

		Triangle_list.at(i) = make_shared<Triangle>();
		//sets the 3 coordinates of the 3 vertexes for a triangle
		//sets the color for each vertex
		//vector 1
		((Triangle_list.at(i))->get_v1()).x = posBuf.at(i * 9 );
		((Triangle_list.at(i))->get_v1()).y = posBuf.at((i * 9) + 1);
		((Triangle_list.at(i))->get_v1()).z = posBuf.at((i * 9) + 2) ; //z 
		((Triangle_list.at(i))->get_v1()).Norm.push_back(norBuf.at(i*9));
		((Triangle_list.at(i))->get_v1()).Norm.push_back( norBuf.at((i*9) + 1));
		((Triangle_list.at(i))->get_v1()).Norm.push_back(norBuf.at((i*9) + 2));

	
		//vector 2
		((Triangle_list.at(i))->get_v2()).x =  posBuf.at((i * 9) + 3);
		((Triangle_list.at(i))->get_v2()).y =  posBuf.at((i * 9) + 4);
		((Triangle_list.at(i))->get_v2()).z =  posBuf.at((i * 9) + 5)  ; 
		((Triangle_list.at(i))->get_v2()).Norm.push_back(norBuf.at((i*9)+3));
		((Triangle_list.at(i))->get_v2()).Norm.push_back(norBuf.at((i*9)+4));
		((Triangle_list.at(i))->get_v2()).Norm.push_back(norBuf.at((i*9)+5));

		
		//vector 3
		((Triangle_list.at(i))->get_v3()).x =  posBuf.at((i * 9) + 6);
		((Triangle_list.at(i))->get_v3()).y =  posBuf.at((i * 9) + 7);
		((Triangle_list.at(i))->get_v3()).z =  posBuf.at((i * 9) + 8) ;  
		((Triangle_list.at(i))->get_v3()).Norm.push_back(norBuf.at((i*9)+6));
		((Triangle_list.at(i))->get_v3()).Norm.push_back( norBuf.at((i*9)+7));
		((Triangle_list.at(i))->get_v3()).Norm.push_back(norBuf.at((i*9)+8));

		//sets the rgb values for entire triangle
		(Triangle_list.at(i))->r = RANDOM_COLORS[i % 7][0] * 255;
		(Triangle_list.at(i))->g = RANDOM_COLORS[i % 7][1] * 255;
		(Triangle_list.at(i))->b = RANDOM_COLORS[i % 7][2] * 255 ;
	

	}
	//sets color per each vertex
	for (unsigned int i = 0; i < posBuf.size()/3; i += 3) {
		//v1
		((Triangle_list.at(i/3))->get_v1()).r = RANDOM_COLORS[(i) % 7][0] * 255;
		((Triangle_list.at(i/3))->get_v1()).g = RANDOM_COLORS[(i) % 7][1] * 255;
		((Triangle_list.at(i/3))->get_v1()).b = RANDOM_COLORS[(i) % 7][2] * 255;

 		//v2
		((Triangle_list.at(i/3))->get_v2()).r = RANDOM_COLORS[(i + 1) % 7][0] * 255;
		((Triangle_list.at(i/3))->get_v2()).g = RANDOM_COLORS[(i + 1) % 7][1] * 255;
		((Triangle_list.at(i/3))->get_v2()).b = RANDOM_COLORS[(i + 1) % 7][2] * 255;

 		//v3
		((Triangle_list.at(i/3))->get_v3()).r = RANDOM_COLORS[(i + 2) % 7][0] * 255 ;
		((Triangle_list.at(i/3))->get_v3()).g = RANDOM_COLORS[(i + 2) % 7][1] * 255 ;
		((Triangle_list.at(i/3))->get_v3()).b = RANDOM_COLORS[(i + 2) % 7][2] * 255 ;

	}
	//holds the z distance of each pixel
	Z_buffer Z_positions(height, width);
	double curr_z;
	Tri_Mesh_to_image(Triangle_list,x_min,x_max,y_min,y_max,width,height);
	//holds Areas of vertices A,B,C
	pair<double, pair<double, double>> Area;
	//holds the rgb values for all the pixels
		int R;
		int G;
		int B;
	
	switch (task)
	{
		//does the bounding boxes 
	case 1:
		// goes through each triangle 
		{for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			//loops over all x and y in the bounding box of a traingle and color them the appropriate color
			for (int y = floor(Triangle_list.at(n)->get_ymin()); y < floor(Triangle_list.at(n)->get_ymax()); y++ ){

				for (int x = floor(Triangle_list.at(n)->get_xmin()); x < floor(Triangle_list.at(n)->get_xmax()); x++ ) {
					
					image->setPixel(x, y, Triangle_list.at(n)->r, Triangle_list.at(n)->g, Triangle_list.at(n)->b);
				}
			}
	}}

		break;
		//use baycentric coordinates to only color in the area of the triangles 
	case 2:

	{	for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {

				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						image->setPixel(x, y, Triangle_list.at(n)->r, Triangle_list.at(n)->g, Triangle_list.at(n)->b);
					}

					
				}
			}


		}}

	break;
		// assign rgb valuees per vertex and then using baycentric coords 
	case 3:
	
		{for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
				
				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						//go back to taking in the vertex as each vertex should be getting a unique rgb value as opposed to each vertex getting one part of the rgb i.e each row of 
						Area = Baycentric_Coord_area(x, y, Triangle_list.at(n)->get_v1().x, Triangle_list.at(n)->get_v1().y, Triangle_list.at(n)->get_v2().x, Triangle_list.at(n)->get_v2().y, Triangle_list.at(n)->get_v3().x, Triangle_list.at(n)->get_v3().y);
						
						//calculates z for the pixel by taking baycentric coord 
						curr_z = (Area.first * Triangle_list.at(n)->get_v1().z) + (Area.second.first * Triangle_list.at(n)->get_v2().z) + (Area.second.second * Triangle_list.at(n)->get_v3().z);
						
						 R = Area.first * Triangle_list.at(n)->get_v1().r + Area.second.first * Triangle_list.at(n)->get_v2().r + Area.second.second * Triangle_list.at(n)->get_v3().r;
						Color_check(R);
						 G = Area.first * Triangle_list.at(n)->get_v1().g + Area.second.first * Triangle_list.at(n)->get_v2().g + Area.second.second * Triangle_list.at(n)->get_v3().g; 
						Color_check(G);
						 B = Area.first * Triangle_list.at(n)->get_v1().b + Area.second.first * Triangle_list.at(n)->get_v2().b + Area.second.second * Triangle_list.at(n)->get_v3().b;
						Color_check(B);
					
						
						//checks if z value is greater than current z-value in place and will write in the z-value
					if( Z_positions.add_z_value(curr_z,x,y)){
							
						image->setPixel(x, y, R, G, B);
					}
					
				}

					
					
				}
			}


		}}

	break;
	//does gradient of blue and  red based on y interpolation
	case 4:
	//gets top and bottom of object in image coords
	{	int object_ymax = floor(point_Mesh_to_image(0,y_max,x_min,x_max,y_min,y_max,width,height).second);
		int object_ymin = floor(point_Mesh_to_image(0,y_min,x_min,x_max,y_min,y_max,width,height).second);

		for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
				pair<double,double> ratio = Baycentric_linear_interpolation(y,object_ymin,object_ymax);
						R = floor(255.00* ratio.second);
						B = floor(255.00*ratio.first);
						G = 0;

				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						image->setPixel(x,y,R,G,B);
					}

					
				}
			}

		}

	}
	break;
	//does gradient of red color based on z-distance interpolation
	case 5:
		{double zmesh_max = vect_max(Zpos);
		double zmesh_min = vect_min(Zpos);
		R = 0;
		G = 0;
		B = 0;
		
		for ( unsigned int n = 0; n < Triangle_list.size(); n++) {
					for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
						for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {


							if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
							//used to interpolate the z coord for the point
							Area = Baycentric_Coord_area(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y);
							curr_z = Triangle_list.at(n)->get_v1().z * Area.first + Triangle_list.at(n)->get_v2().z * Area.second.first + Triangle_list.at(n)->get_v3().z * Area.second.second ;
								//calculate color based on z 
								R = Baycentric_linear_interpolation(curr_z,zmesh_min,zmesh_max).second * 255;
								
								if( Z_positions.add_z_value(curr_z,x,y)){
								image->setPixel(x,y,R,G,B);	
								}

								
							}
						}
						}
					}
		
	}

		break;
		//does the  coloring based on the normal values
	case 6:
	{
		for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
				
				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						//go back to taking in the vertex as each vertex should be getting a unique rgb value as opposed to each vertex getting one part of the rgb i.e each row of 
						Area = Baycentric_Coord_area(x, y, Triangle_list.at(n)->get_v1().x, Triangle_list.at(n)->get_v1().y, Triangle_list.at(n)->get_v2().x, Triangle_list.at(n)->get_v2().y, Triangle_list.at(n)->get_v3().x, Triangle_list.at(n)->get_v3().y);
						
						//calculates z for the pixel by taking baycentric coord 
						curr_z = (Area.first * Triangle_list.at(n)->get_v1().z) + (Area.second.first * Triangle_list.at(n)->get_v2().z) + (Area.second.second * Triangle_list.at(n)->get_v3().z);
						
						 R = 255*(0.5*(Area.first * Triangle_list.at(n)->get_v1().Norm[0] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[0] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[0]) +0.5);
						Color_check(R);
						 G = 255*(0.5*(Area.first * Triangle_list.at(n)->get_v1().Norm[1] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[1] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[1]) + 0.5); 
						Color_check(G);
						 B = 255 * (0.5*(Area.first * Triangle_list.at(n)->get_v1().Norm[2] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[2] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[2])+0.5);
						Color_check(B);
					
						
						//checks if z value is greater than current z-value in place and will write in the z-value
					if( Z_positions.add_z_value(curr_z,x,y)){
							
						image->setPixel(x, y, R, G, B);
					}
					
				}

					
					
				}
			}


		}



	break;


	}
	//makes lighting based on interpolated normals 
	case 7: 
	{
		for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
				
				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						//go back to taking in the vertex as each vertex should be getting a unique rgb value as opposed to each vertex getting one part of the rgb i.e each row of 
						Area = Baycentric_Coord_area(x, y, Triangle_list.at(n)->get_v1().x, Triangle_list.at(n)->get_v1().y, Triangle_list.at(n)->get_v2().x, Triangle_list.at(n)->get_v2().y, Triangle_list.at(n)->get_v3().x, Triangle_list.at(n)->get_v3().y);
						
						//calculates z for the pixel by taking baycentric coord 
						curr_z = (Area.first * Triangle_list.at(n)->get_v1().z) + (Area.second.first * Triangle_list.at(n)->get_v2().z) + (Area.second.second * Triangle_list.at(n)->get_v3().z);
					
					vector<double> Interpolated_Normals = {(Area.first * Triangle_list.at(n)->get_v1().Norm[0] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[0] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[0]),(Area.first * Triangle_list.at(n)->get_v1().Norm[1] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[1] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[1]), (Area.first * Triangle_list.at(n)->get_v1().Norm[2] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[2] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[2])};
					
					
					//calculates the light scalar for each pixel	
					double	c = simple_light_calc( Interpolated_Normals);
						R = c * 255;

						Color_check(R);
						B = c * 255;
						Color_check(B);
						G = c * 255;		
						Color_check(G);
						
						//checks if z value is greater than current z-value in place and will write in the z-value
					if( Z_positions.add_z_value(curr_z,x,y)){
							
						image->setPixel(x, y, R, G, B);
					}
					
				}

					
					
				}
			}


		}

		break;
	}
	
	case 8:
	//apply rotation and does lighting
	{
		for (unsigned int n = 0; n < Triangle_list.size(); n++) {
			for (int y = Triangle_list.at(n)->get_ymin(); y < Triangle_list.at(n)->get_ymax(); y++) {
				
				for (int x = Triangle_list.at(n)->get_xmin(); x < Triangle_list.at(n)->get_xmax(); x++) {
					
						
					if( Baycentric_coord_check(x, y,Triangle_list.at(n)->get_v1().x,Triangle_list.at(n)->get_v1().y,Triangle_list.at(n)->get_v2().x,Triangle_list.at(n)->get_v2().y,Triangle_list.at(n)->get_v3().x,Triangle_list.at(n)->get_v3().y)){
						//go back to taking in the vertex as each vertex should be getting a unique rgb value as opposed to each vertex getting one part of the rgb i.e each row of 
						Area = Baycentric_Coord_area(x, y, Triangle_list.at(n)->get_v1().x, Triangle_list.at(n)->get_v1().y, Triangle_list.at(n)->get_v2().x, Triangle_list.at(n)->get_v2().y, Triangle_list.at(n)->get_v3().x, Triangle_list.at(n)->get_v3().y);
						
						//calculates z for the pixel by taking baycentric coord 
						curr_z = (Area.first * Triangle_list.at(n)->get_v1().z) + (Area.second.first * Triangle_list.at(n)->get_v2().z) + (Area.second.second * Triangle_list.at(n)->get_v3().z);
					
					vector<double> Interpolated_Normals = {(Area.first * Triangle_list.at(n)->get_v1().Norm[0] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[0] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[0]),(Area.first * Triangle_list.at(n)->get_v1().Norm[1] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[1] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[1]), (Area.first * Triangle_list.at(n)->get_v1().Norm[2] + Area.second.first * Triangle_list.at(n)->get_v2().Norm[2] + Area.second.second * Triangle_list.at(n)->get_v3().Norm[2])};
					
					
					//calculates the light scalar for each pixel	
					double c = simple_light_calc( Interpolated_Normals);
						R = c *255;
						Color_check(R);
						B = c*255;
						Color_check(B);
						G = c*255;		
						Color_check(G);
						
						//checks if z value is greater than current z-value in place and will write in the z-value
					if( Z_positions.add_z_value(curr_z,x,y)){
							  
						image->setPixel(x, y, R, G, B);
					}
					
				}

					
					
				}
			}


		}

		break;
	}

	default:
	std:: cout << "task number must be within range [1,8]" << endl;
		return 1;
		break;
}
	





	//writes out the image to certain filename.
	image->writeToFile(output_name);


	return 0;
}
