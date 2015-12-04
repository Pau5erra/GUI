#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<UIElement*>* tmp = list_elements.start;
	while (tmp){
		tmp->data->Draw();
		tmp = tmp->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------
UIImage::UIImage()
{
}

UIImage* j1Gui::addImage(p2SString name, iPoint position,  SDL_Rect section){
	UIImage* new_image = new UIImage();
	
	new_image->image = atlas;
	new_image->position = position;
	new_image->getRect = section;
	new_image->name = name;

	list_elements.add(new_image);

	return new_image;
}

UIImage* j1Gui::addImage(p2SString name, iPoint position, SDL_Rect section, SDL_Texture* texture){
	UIImage* new_image = new UIImage();

	new_image->position = position;
	new_image->image = texture;
	new_image->getRect = section;
	new_image->name = name;
	list_elements.add(new_image);

	return new_image;
}

bool UIImage::Draw(){

	App->render->Blit(image, position.x, position.y, &getRect);

	return true;

}

	UIText::UIText(){

		};

UIText* j1Gui::addText(p2SString name, char* text, iPoint position){
	UIText* new_text = new UIText(text, position);
	
	new_text->position = position;
	new_text->text_texture = App->font->Print(text);
	list_elements.add(new_text);

	return new_text;
}

	bool UIText::Draw(){
		App->render->Blit(text_texture, position.x, position.y);

		return true;
	}

	UIButton::UIButton(UIImage* image, UIText* text){
		this->image = image;
		this->text = text;
	}

/*UIButton* j1Gui::addButton(p2SString name, UIImage image, UIText text){
	UIButton* new_button = new UIButton();
	new_button->name = name;
	new_button->image = image;
	new_button->text = text;
	new_button->position = image.position;

	return new_button;
}

bool UIButton::Update(){

	return true;

}

UIInput* j1Gui::addInput(p2SString name, UIImage image, UIText default_text){
	UIInput* new_input = new UIInput();

	new_input->name = name;
	new_input->image = image;
	new_input->default_text = default_text;
	new_input->position = image.position;

	return new_input;
}

bool UIInput::Update(){

	return true;

}
*/