
#ifndef BUTTON_H
#define BUTTON_H

#include <rt2d/entity.h>
#include <rt2d/text.h>
#include <functional>
class MyScene;

class Button : public Entity
{
public:

   // Button constructor
   Button(std::string name, RGBAColor c);

   // Button destructor
   ~Button();

   // Updates the button every frame
   void update(float deltaTime);


   // Checks if the button is being clicked and runs the function pointed to by buttonRun
   void checkClick();

   void setButtonRun(std::function<void()> value) { buttonRun = value; }
   // Text setters:
   // A setter for the horizontal text offset from the button
   void setTextOffset(float x) { display->position.x = x; }

   // A setter for the text scaling
   void setTextScale(float scale);


private:
	std::function<void()> buttonRun = nullptr;

	// The text which will be displayed on the button
	Text* display;
};

#endif // !BUTTON_H
