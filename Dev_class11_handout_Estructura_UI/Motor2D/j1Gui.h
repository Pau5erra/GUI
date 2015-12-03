#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "SDL_TTF\include\SDL_ttf.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_ID{
	TEXT = 0,
	IMAGE,
	BUTTON,
};

enum UI_BUTTON_EVENTS{
	MOUSE_ENTER = 0,
	MOUSE_LEAVE,
	MOUSE_PRESS,
};

class UIElement
{
public:
	UI_ID type;
	p2SString name;
	iPoint position;
	
public:
	UIElement(){};
	~UIElement(){};

	virtual bool Update(){ return true; }
	virtual bool Draw(){ return true; }
};



class UIImage : public UIElement
{
public:
	SDL_Texture* image;
	SDL_Rect getRect;

public:
	UIImage(SDL_Texture* new_texture, SDL_Rect rect, iPoint position);

	~UIImage(){}

	bool Draw();

};

class UIText : public UIElement
{
public:
	SDL_Texture* text_texture;

public:
	UIText(char* text, iPoint position);

	~UIText(){}

	bool Draw();

};

class UIButton : public UIElement
{
public:
	UIImage* image;
	UIText* text;
	j1Module* listener;

public:
	UIButton(UIImage* image, UIText* text);
	~UIButton(){}

	bool Update();
};
/*
class UIInput : public UIElement
{
public:
	UIImage image;
	UIText default_text;

public:

	UIInput(){}
	~UIInput(){}

	bool Update();
};*/
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UIImage* addImage(p2SString name, iPoint position, SDL_Rect section);
	UIImage* addImage(p2SString name, iPoint position, SDL_Rect section, SDL_Texture* texture);
	UIText* addText(p2SString name, char* text, iPoint position);
	//UIButton* addButton(p2SString name, UIImage image, UIText text);
	//UIInput* addInput(p2SString name, UIImage image, UIText default_text);

	const SDL_Texture* GetAtlas() const;

private:

	p2List<UIElement*> list_elements;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__