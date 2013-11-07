/*

Level File Format (.lvl):

MUSIC FILENAME\n
BACKGROUND FILENAME\n

for every spritesheet
	SPRITE SPRITESHEET_IMAGE, SPRITESHEET_NAME

for every sequence
	SPRITESHEET_NAME, SEQUENCE_NAME, FRAME_TIME

for every coord
	COORD SPRITESHEET_NAME, SEQUENCE_NAME, X, Y, W, H

for every object
	OBJECT SPRITESHEET, POSITION, FRAMES, SEQUENCE \n
*/
#include <SDL.h>
#include "level.h"
#include "object.h"
#include <string.h>
#include <iostream>
#include "template.h"
#include "sound.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

static enum FileCommand { cmd_back, cmd_music, cmd_spritesheet, cmd_obj, cmd_coord, cmd_sequence};
static std::map<std::string, FileCommand> FileCommand_vals;

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


Level::Level(SDL_Renderer* _renderer, std::string _filename)
{
	renderer = _renderer;
	filename = _filename;
	FileCommand_vals["MUSIC"] = cmd_music;
	FileCommand_vals["SEQUENCE"] = cmd_sequence;
	FileCommand_vals["COORD"] = cmd_coord;
	FileCommand_vals["BACKGROUND"] = cmd_back;
	FileCommand_vals["SPRITE"] = cmd_spritesheet;
	FileCommand_vals["OBJECT"] = cmd_obj;
}

void Level::clean()
{
	music->free();
}

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    unsigned int pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void Level::addObject(Object obj)
{
	for(int i = 0; i <= objlist.size(); i++)
	{
		Object test = objlist[i];
		if(&test == &obj)
			return;
	}
	objlist.push_back(obj);
}

void Level::loadToWorld(World* wrld)
{
	wrld->clearObjects();
	for(int i = 0; i < objlist.size(); i++)
	{
		wrld->addObject(objlist[i]);
	}
	wrld->setBackground(&back);
	printf("\ndone loadToWorld\n");
}

void Level::load_music()
{
	printf(music_file.c_str());
	printf("\n");
	music = new Sound(music_file,true);
}

void Level::playMusic()
{
	music->play();
}
void Level::stopMusic()
{
	music->stop();
}

void Level::newMusic(std::string filename)
{
	music_file = filename;
	load_music();
}

bool Level::Load()
{
	std::string fix;
	std::string line;
	std::ifstream myfile (filename);
	std::vector<std::string> vec;
	//switchTest();
	if(myfile.is_open())
	{
		while (getline(myfile,line))
		{
			split(line, vec, ' ');
			if(vec.size() > 0)
			{
				fix = vec[0].substr(0,vec[0].size()-1);
				switch(FileCommand_vals[fix])
				{
					case cmd_music:
						printf("M %d\n",vec.size());
						music_file = vec[1];
						load_music();
						printf("\n");
						break;
					case cmd_obj:
						printf("O %d\n",vec.size());
						printf(vec[1].c_str());
						printf(vec[2].c_str());
						printf(vec[3].c_str());
						printf(vec[4].c_str());
						printf(vec[5].c_str());
						printf(vec[6].c_str());
						objlist.push_back(Object(sprites[vec[1]], atoi(vec[2].c_str()), Vector2D(atoi(vec[3].c_str()),atoi(vec[4].c_str())), renderer, atoi(vec[5].c_str()), vec[6]));
						printf("\n");
						break;
					case cmd_spritesheet:
						printf("SS %d\n",vec.size());
						printf(vec[1].c_str());
						printf(vec[2].c_str());
						sprites[vec[2]] = spriteSheet((char *)vec[1].c_str(), renderer);
						printf("\n");
						break;
					case cmd_back:
						//printf(vec[1]);
						printf("B %d\n",vec.size());
						printf(vec[1].c_str());
						back = background((char *)vec[1].c_str(), renderer);
						printf("\n");
						break;
					case cmd_coord:
						printf("C %d\n",vec.size());
						printf(vec[1].c_str());
						printf(vec[3].c_str());
						printf(vec[4].c_str());
						printf(vec[5].c_str());
						printf(vec[6].c_str());
						printf(vec[2].c_str());
						sprites[vec[1]].addCoords(atoi(vec[3].c_str()), atoi(vec[4].c_str()), atoi(vec[5].c_str()), atoi(vec[6].c_str()), vec[2]);
						printf("\n");
					case cmd_sequence:
						printf("S %d\n",vec.size());
						printf(vec[1].c_str());
						printf(vec[2].c_str());
						printf(vec[3].c_str());
						printf("\n");
						sprites[vec[1]].newSequence(vec[2],atoi(vec[3].c_str()));
					default:
						break;
				}
			}
		}
		myfile.close();
		return true;
	}
	else
	{
		return false;
	}
}