#include "World.h"
#include "Datacore.h"

namespace{
	const u8 MAX_BUFFER_SIZE = 64;
	const u8 MAX_PATH_SIZE = 32;

	u16 GetNumCharCount(u8 *src){
		u16 count = 0;
		while(IS_NUMBER(*src)){
			++count;
			++src;
		}

		return count;
	}
}


//TODO: Add functionality later...
World::World(){
	plane = new Plane(1, 1);

	//load environmental textures
	Datacore::texture_grass   = plane->LoadBMP("Assets/grass.bmp");
	Datacore::texture_ground  = plane->LoadBMP("Assets/ground.bmp");
	Datacore::texture_treeTop = plane->LoadBMP("Assets/tree_top.bmp");
	Datacore::texture_treeBot = plane->LoadBMP("Assets/tree_bot.bmp");
	Datacore::texture_dirt	  = plane->LoadBMP("Assets/dirt.bmp");
	Datacore::texture_rock	  = plane->LoadBMP("Assets/rock.bmp");

	//load player textures
	Datacore::texture_player_idle_f  = plane->LoadBMP("Assets/p_idle_front");
	Datacore::texture_player_idle_b  = plane->LoadBMP("Assets/p_idle_back");
	Datacore::texture_player_idle_l  = plane->LoadBMP("Assets/p_idle_left");
	Datacore::texture_player_idle_r  = plane->LoadBMP("Assets/p_idle_right");
	Datacore::texture_player_walk_u1 = plane->LoadBMP("Assets/p_walk_up1");
	Datacore::texture_player_walk_u2 = plane->LoadBMP("Assets/p_walk_up2");
	Datacore::texture_player_walk_d1 = plane->LoadBMP("Assets/p_walk_down1");
	Datacore::texture_player_walk_d2 = plane->LoadBMP("Assets/p_walk_down2");
	Datacore::texture_player_walk_l1 = plane->LoadBMP("Assets/p_walk_left1");
	Datacore::texture_player_walk_l2 = plane->LoadBMP("Assets/p_walk_left2");
	Datacore::texture_player_walk_r1 = plane->LoadBMP("Assets/p_walk_right1");
	Datacore::texture_player_walk_r2 = plane->LoadBMP("Assets/p_walk_right2");

	//load world...
	ifstream myfile(LEVEL_0);

	char buffer[::MAX_BUFFER_SIZE];
	char path[::MAX_PATH_SIZE];

	if (myfile.is_open())
	{
		string line;
		unsigned char len = 0;

		bool loadLevelData = true;

		while ( getline (myfile,line) )
		{
			line.copy(buffer, len = line.length());
			buffer[len] = '\0';

			if(IS_EMPTY_LINE(buffer[0])){
				continue;
			}
			else if(LOAD_TEXTURE(buffer[0])){
				//Setting buffer size...
				numTextures = buffer[1] - ASCII_ZERO;
				textureBuffer = (u8*)malloc(MAX_PATH_SIZE * numTextures);

				loadLevelData = false;
				continue;
			}
			else if(LOAD_LEVELDATA(buffer[0])){
				//Setting buffer size...

				//Adding 1 to accomodate for comma...
				u8 numStride = ::GetNumCharCount((u8*)&buffer[1]) + 1;

				levelWidth = std::stoi(&buffer[1]);
				levelHeight = std::stoi(&buffer[1 + numStride]);
		
				levelBuffer = (u8*)malloc(levelWidth * levelHeight);
				//memset(levelBuffer, 0, sizeof(levelBuffer));

				loadLevelData = true;
				continue;
			}
			else if(loadLevelData){
				//TODO: May need to put this elsewhere so it doesn't persist
				static u16 levelIndex = 0;

				for(u16 i = 0, count = 0; count < levelWidth; ++i){
					if(IS_NUMBER(buffer[i])){
						levelBuffer[levelIndex++] = buffer[i];
						++count;
					}
				}

				continue;
			}

			unsigned char commaLen = FindChar(buffer, ',');
			static u8 texIndex = 0;


			//Found textures...
			if(commaLen > 0){
				//strcpy_s(path, commaLen, buffer);
				strcpy(path, buffer);
				path[commaLen - 1] = '\0';
				memcpy(&textureBuffer[texIndex], &path, MAX_PATH_SIZE);
				texIndex += MAX_PATH_SIZE -1;
				continue;
			}

			//load textures...
			//string filePath = 
		}

		myfile.close();
	}

	else cout << "Unable to open file"; 
}

unsigned char World::FindChar(const char* buffer, const char& c){
	//TODO: Search for char c, if found return true...
	char* value = (char*)buffer;
	unsigned char len = 0;

	while(value != '\0'){
		++len;
		if(*value == c){
			return len;
		}
		++value;
	}

	return len = 0;
}

//TODO: Add functionality later...
World::~World(){
	delete plane;
	plane = NULL;
}

void World::_WorldToScreen(float &x, float &y) {
	float spacing = 1.0f;
	x = (spacing * x) - this->levelWidth / 3;
	x += 7 - (2 * x);
	y = (spacing * y) - this->levelHeight / 2;
}

void World::Update(const float& deltaTime){
	plane->Update(deltaTime);
}

void World::Render(const Camera& camera){	
	/*int levelLength = levelHeight * levelWidth;
	int index = levelLength;
	for(int i = 0; i < levelHeight; i++){
		for(int j = 0; j < levelWidth; j++) {
			float x = j;
			float y = i;
			_WorldToScreen(x,y);
			plane->SetPosition(vec3(x, y, 0));
			if(levelBuffer[index] == '0'){
				plane->textureID = Datacore::texture_grass;
				plane->Render(camera);
				index--;
			} else if(levelBuffer[index] == '1'){
				plane->textureID = Datacore::texture_treeTop;
				plane->Render(camera);
				index--;
			} else if(levelBuffer[index] == '2'){
				plane->textureID = Datacore::texture_treeBot;
				plane->Render(camera);
				index--;
			} else if(levelBuffer[index] == '3'){
				plane->textureID = Datacore::texture_ground;
				plane->Render(camera);
				index--;
			} else if(levelBuffer[index] == '4'){
				plane->textureID = Datacore::texture_dirt;
				plane->Render(camera);
				index--;
			} else if(levelBuffer[index] == '5'){
				plane->textureID = Datacore::texture_rock;
				plane->Render(camera);
				index--; 
			} else index--;
		}
	}*/

	plane->SetPosition(vec3(0,0,0));
	plane->textureID = Datacore::texture_player_idle_f;
	plane->Render(camera);

}