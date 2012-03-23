#include "RocEye.h"

#include <iostream>

#ifdef WIN32
//windows uses a different name for isnan(), and defines it in float.h
#define isnan _isnan
#include <float.h>
#endif

#define GETLINE_SKIP_BLANK_AND_COMMENT(x,y) getline(x, y); if (y == "" || y[0] == '#') continue;

#define SPLIT_STRING_ON_SEMICOLON(x) int first_of = x.find_first_of(':'); if (first_of < 0) {first_of = 0;} string key = x.substr(1, first_of - 1); string val = x.substr(first_of+1);

#define TRY_GET_FLOAT(x,y,z) if (x == #y) y = static_cast<float>(strtod(z.c_str(), NULL));
#define ELSE_TRY_GET_FLOAT(x, y, z) else TRY_GET_FLOAT(x,y,z)

#define TRY_GET_STRING(x,y,z) if (x == #y) y = z;

void RocEye::loadSceneFile(void)
{
	using namespace std;
	
	ifstream sceneFile;
	sceneFile.open("scene.cfg");
	
	string line;
	
	while (sceneFile.good())
	{
		GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
		
		if (line == "{")
		{
			bool noError = true;
			
			//need to manually skip empty lines and comments here
			while (true)
			{
				GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
				break;
			}
			
			SPLIT_STRING_ON_SEMICOLON(line);
			
			if (key == "MODEL")
			{
				string mesh = "";
				float x = std::numeric_limits<float>::quiet_NaN(); //this is not a valid value
				float y = std::numeric_limits<float>::quiet_NaN();
				float z = std::numeric_limits<float>::quiet_NaN();
			
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					
					SPLIT_STRING_ON_SEMICOLON(line)
					
					TRY_GET_STRING(key, mesh, val)
					ELSE_TRY_GET_FLOAT(key, x, val)
					ELSE_TRY_GET_FLOAT(key, y, val)
					ELSE_TRY_GET_FLOAT(key, z, val)
				}
				
				if (mesh != "" && !isnan(x) && !isnan(y) && !isnan(z))
				{
					createEntity(mesh, Ogre::Vector3(x,y,z));
				}
				else
				{
					cerr << "Could not parse model declaration in scene.cfg" << endl;
				}
			}//end model
			else if (key == "PLANE")
			{
				string type = val;
				
				string material = "";
				float normal_x = std::numeric_limits<float>::quiet_NaN();
				float normal_y = std::numeric_limits<float>::quiet_NaN();
				float normal_z = std::numeric_limits<float>::quiet_NaN();
				float updir_x = std::numeric_limits<float>::quiet_NaN();
				float updir_y = std::numeric_limits<float>::quiet_NaN();
				float updir_z = std::numeric_limits<float>::quiet_NaN();
				float height = std::numeric_limits<float>::quiet_NaN();
				float width = std::numeric_limits<float>::quiet_NaN();
				float dist_from_origin = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
				
					TRY_GET_STRING(key, material, val)
					ELSE_TRY_GET_FLOAT(key, normal_x, val)
					ELSE_TRY_GET_FLOAT(key, normal_y, val)
					ELSE_TRY_GET_FLOAT(key, normal_z, val)
					ELSE_TRY_GET_FLOAT(key, updir_x, val)
					ELSE_TRY_GET_FLOAT(key, updir_y, val)
					ELSE_TRY_GET_FLOAT(key, updir_z, val)
					ELSE_TRY_GET_FLOAT(key, height, val)
					ELSE_TRY_GET_FLOAT(key, width, val)
					ELSE_TRY_GET_FLOAT(key, dist_from_origin, val)
				}
				
				if (material != "" && !isnan(normal_x) && !isnan(normal_y) && !isnan(normal_z) && !isnan(updir_x) && !isnan(updir_y) && !isnan(updir_z) && !isnan(height) && !isnan(width) && !isnan(dist_from_origin))
				{
					Ogre::Vector3 normal(normal_x, normal_y, normal_z);
					Ogre::Vector3 up(updir_x, updir_y, updir_z);
					createPlane(normal, dist_from_origin, width, height, material, up);
					
					if (type == "DOUBLE")
					{
						//make the plane double-sided by creating a second one with the opposite normal vector, in the same location
						createPlane(-normal, -dist_from_origin, width, height, material, up);
					}
				}
				else
				{
					cerr << "Could not parse plane definition in scene.cfg" << endl;
				}				
			}//end plane
			else if (key == "VIEWPORT_COLOUR")
			{
				float red = std::numeric_limits<float>::quiet_NaN();
				float green = std::numeric_limits<float>::quiet_NaN();
				float blue = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
				
					TRY_GET_FLOAT(key, red, val)
					ELSE_TRY_GET_FLOAT(key, green, val)
					ELSE_TRY_GET_FLOAT(key, blue, val)
				}
				
				if (!isnan(red) && !isnan(green) && !isnan(blue))
				{
					mViewport->setBackgroundColour(Ogre::ColourValue(red, green, blue));
				}
				else
				{
					cerr << "Could not parse viewport colour definition in scene.cfg" << endl;
				}
			}//end viewport colour
			else if (key == "SHADOWS")
			{
				//the user wants shadows!
				if (val == "TEXTURE_MODULATIVE")
				{
					mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
				}
				else if (val == "STENCIL_MODULATIVE")
				{
					mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
				}
				else if (val == "STENCIL_ADDITIVE")
				{
					mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
				}
				else if (val != "NONE") //"NONE" is a special do-nothing value
				{
					cerr << "Unrecognized shadow type in scene.cfg: " << val << endl;
				}
			}//end shadow
			else if (key == "LIGHT")
			{
				string type = val;
				
				float diffuse_red = std::numeric_limits<float>::quiet_NaN();
				float diffuse_green = std::numeric_limits<float>::quiet_NaN();
				float diffuse_blue = std::numeric_limits<float>::quiet_NaN();
				float specular_red = std::numeric_limits<float>::quiet_NaN();
				float specular_green = std::numeric_limits<float>::quiet_NaN();
				float specular_blue = std::numeric_limits<float>::quiet_NaN();
				float pos_x = std::numeric_limits<float>::quiet_NaN();
				float pos_y = std::numeric_limits<float>::quiet_NaN();
				float pos_z = std::numeric_limits<float>::quiet_NaN();
				float dir_x = std::numeric_limits<float>::quiet_NaN();
				float dir_y = std::numeric_limits<float>::quiet_NaN();
				float dir_z = std::numeric_limits<float>::quiet_NaN();
				float inner_angle = std::numeric_limits<float>::quiet_NaN();
				float outer_angle = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
				
					TRY_GET_FLOAT(key, diffuse_red, val)
					ELSE_TRY_GET_FLOAT(key, diffuse_green, val)
					ELSE_TRY_GET_FLOAT(key, diffuse_blue, val)
					ELSE_TRY_GET_FLOAT(key, specular_red, val)
					ELSE_TRY_GET_FLOAT(key, specular_green, val)
					ELSE_TRY_GET_FLOAT(key, specular_blue, val)
					ELSE_TRY_GET_FLOAT(key, pos_x, val)
					ELSE_TRY_GET_FLOAT(key, pos_y, val)
					ELSE_TRY_GET_FLOAT(key, pos_z, val)
					ELSE_TRY_GET_FLOAT(key, dir_x, val)
					ELSE_TRY_GET_FLOAT(key, dir_y, val)
					ELSE_TRY_GET_FLOAT(key, dir_z, val)
					ELSE_TRY_GET_FLOAT(key, inner_angle, val)
					ELSE_TRY_GET_FLOAT(key, outer_angle, val)
				}
				
				//we'll handle these NOW to avoid copy-pasting, but the angles only need to be handled inside the spotlight
				Ogre::ColourValue dColour(diffuse_red, diffuse_green, diffuse_blue);
				Ogre::ColourValue sColour(specular_red, specular_green, specular_blue);
				Ogre::Vector3 pos(pos_x, pos_y, pos_z);
				Ogre::Vector3 dir(dir_x, dir_y, dir_z);
				
				if (type == "POINT" && !isnan(diffuse_red) && !isnan(diffuse_green) && !isnan(diffuse_blue) && !isnan(specular_red) && !isnan(specular_green) && !isnan(specular_blue) && !isnan(pos_x) && !isnan(pos_y) && !isnan(pos_z))
				{
					createPointLight(pos, dColour, sColour);
				}
				else if (type == "DIRECTIONAL" && !isnan(diffuse_red) && !isnan(diffuse_green) && !isnan(diffuse_blue) && !isnan(specular_red) && !isnan(specular_green) && !isnan(specular_blue) && !isnan(dir_x) && !isnan(dir_y) && !isnan(dir_z))
				{
					createDirectionalLight(dir, dColour, sColour);
				}
				else if(type == "SPOTLIGHT" && !isnan(diffuse_red) && !isnan(diffuse_green) && !isnan(diffuse_blue) && !isnan(specular_red) && !isnan(specular_green) && !isnan(specular_blue) && !isnan(pos_x) && !isnan(pos_y) && !isnan(pos_z) && !isnan(dir_x) && !isnan(dir_y) && !isnan(dir_z) && !isnan(inner_angle) && !isnan(outer_angle))
				{
					createSpotLight(pos, dir, dColour, sColour, Ogre::Degree(inner_angle), Ogre::Degree(outer_angle));
				}
				else
				{
					cerr << "Error parsing light in scene.cfg. Type given as: " << type << endl;
					continue;
				}
			}//end light
			else if (key == "PORTRAIT")
			{
				string type = val;
				
				Ogre::String material = "";
				float x = std::numeric_limits<float>::quiet_NaN();
				float y = std::numeric_limits<float>::quiet_NaN();
				float z = std::numeric_limits<float>::quiet_NaN();
				float diameter = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
					
					TRY_GET_STRING(key, material, val)
					ELSE_TRY_GET_FLOAT(key, x, val)
					ELSE_TRY_GET_FLOAT(key, y, val)
					ELSE_TRY_GET_FLOAT(key, z, val)
					ELSE_TRY_GET_FLOAT(key, diameter, val)
				}
				
				Ogre::Vector3 center(x,y,z);
				
				if (material != "" && ! center.isNaN() && !isnan(diameter))
				{
					if (val == "CUBE")
					{
						createPortraitCube(center, diameter, material);
					}
					else if (val == "PILLAR")
					{
						createPortraitPillar(center, diameter, material);
					}
				}
			}//end cube
			else if (key == "PARTICLE")
			{
				Ogre::String script = "";
				float x = std::numeric_limits<float>::quiet_NaN();
				float y = std::numeric_limits<float>::quiet_NaN();
				float z = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
					
					TRY_GET_STRING(key, script, val)
					ELSE_TRY_GET_FLOAT(key, x, val)
					ELSE_TRY_GET_FLOAT(key, y, val)
					ELSE_TRY_GET_FLOAT(key, z, val)
				}
				
				Ogre::Vector3 pos(x,y,z);
				
				if (script != "" && ! pos.isNaN())
				{
					createParticleSystem(pos, script);
				}
			}
			else if (key == "SPHERE")
			{
				string material;
				float x = std::numeric_limits<float>::quiet_NaN();
				float y = std::numeric_limits<float>::quiet_NaN();
				float z = std::numeric_limits<float>::quiet_NaN();
				float radius = std::numeric_limits<float>::quiet_NaN();
				float step_size = std::numeric_limits<float>::quiet_NaN();
				
				while (sceneFile.good() && noError && line != "}")
				{
					GETLINE_SKIP_BLANK_AND_COMMENT(sceneFile, line)
					SPLIT_STRING_ON_SEMICOLON(line)
					
					TRY_GET_STRING(key, material, val)
					ELSE_TRY_GET_FLOAT(key, x, val)
					ELSE_TRY_GET_FLOAT(key, y, val)
					ELSE_TRY_GET_FLOAT(key, z, val)
					ELSE_TRY_GET_FLOAT(key, radius, val)
					ELSE_TRY_GET_FLOAT(key, step_size, val)
				}
				
				Ogre::Vector3 center(x,y,z);
				
				if (material != "" && !center.isNaN() && !isnan(radius) && !isnan(step_size))
				{
					createSphere(center, material, radius, step_size);
				}
				
			}
			
		}
	}
}
