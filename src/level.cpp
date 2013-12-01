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
#include <vector>
#include <map>
#include <algorithm>
#include "level.h"
#include "world.h"

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
	std::string cut;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
		cut = txt.substr( initialPos, pos - initialPos + 1 );
		cut = cut.substr(0, cut.size()-1);
        strs.push_back( cut );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( trim(txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 )) );

    return strs.size();
}

void Level::addObject(Object obj)
{
	for(int i = 0; i < objlist.size(); i++)
	{
		Object test = objlist[i];
		if(&test == &obj)
			return;
	}
	//printf("pushing back...\n");
	objlist.push_back(obj);
}

void Level::loadToWorld(World* wrld)
{
	wrld->clearObjects();
	//printf("SIZE %d\n", objlist.size());
	for(int i = 0; i < objlist.size(); i++)
	{
		//printf("OBJECT-POS: %d %d\n", objlist[i].getPosition().xV, objlist[i].getPosition().yV);
		wrld->addObject(objlist[i]);
	}
	wrld->setBackground(&back);
	//printf("\ndone done\n");
}

void Level::load_music()
{
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
	if(myfile.is_open())
	{
		while (getline(myfile,line))
		{
			split(line, vec, ' ');
			if(vec.size() > 0)
			{
				spriteSheet sprite;
				Vector2D vect;
				fix = vec[0];
				int frame, damage;
				std::string seq;
				switch(FileCommand_vals[fix])
				{
					case cmd_music:
						music_file = vec[1];
						load_music();
						break;
					case cmd_obj:
						damage = atoi(vec[5].c_str());
						frame = atoi(vec[2].c_str());
						sprite = sprites[vec[1]];
						seq = vec[6];
						vect = Vector2D(atoi(vec[3].c_str()),atoi(vec[4].c_str()));
						//printf("Adding Object: (%d,%d)\n", vect.xV, vect.yV);
						addObject(Object(sprite, frame, vect, renderer, damage, seq));
						break;
					case cmd_spritesheet:
						printf("STARTING SPRITE: %s\n",vec[2].c_str());
						sprites[vec[2]] = spriteSheet(vec[1].c_str(), renderer);
						break;
					case cmd_back:
						back = background((char *)vec[1].c_str(), renderer);
						break;
					case cmd_coord:
						sprites[vec[1]].addCoords(atoi(vec[3].c_str()), atoi(vec[4].c_str()), atoi(vec[5].c_str()), atoi(vec[6].c_str()), vec[2]);
					case cmd_sequence:
						printf("%s GETS NEW SEQ %s\n",vec[1].c_str(), vec[2].c_str());
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