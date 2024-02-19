#pragma once

#include <string>
#include "imgui.h" 

enum class ButtonState { Empty, X, O };
enum class GameState { Game_In_Progress, Done }; 

struct ImGuiButtonData {
	int id;					// id for button
	ImVec2 position;		// position of button 
	std::string text;		// text display on button 
	ButtonState state; 
};

class Board {
public:
	Board();
	void display();
	void handleButtonClick(int row, int col); 
	bool checkWinner(char mark); 
	bool xWins();
	bool oWins();
	bool isFull();
	void clearBoard(); 

private:
	int markCount;
	ImGuiButtonData buttons[3][3];
	GameState gameState; 
};
