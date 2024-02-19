#include "Board.h"

Board::Board(){
	markCount = 0;
	gameState = GameState::Game_In_Progress;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			buttons[row][col].id = row * 3 + col;	// id for each button
			buttons[row][col].position = ImVec2(60, 60);
			buttons[row][col].text = "   ";
			buttons[row][col].state = ButtonState::Empty; 
		}
	}

}

void Board::display() {

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			ImGui::PushID(buttons[row][col].id);       // unique ID for each button

			std::string buttonText;

			switch (buttons[row][col].state) {
			case ButtonState::X:
				buttonText = 'X';
				break;
			case ButtonState::O:
				buttonText = 'O';
				break;
			case ButtonState::Empty:
			default:
				buttonText = ' ';
				break;
			}
			
			// Render the button with disabled functionality if the game is not in progress
			if (gameState != GameState::Game_In_Progress) {
				ImGui::Button(buttonText.c_str(), ImVec2(60, 60));
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f); // Dim the button
				ImGui::PopStyleVar();
			}
			
			else {
				// Render the button with normal functionality
				if (ImGui::Button(buttonText.c_str(), ImVec2(60, 60)) && buttons[row][col].state == ButtonState::Empty) {
					handleButtonClick(row, col);
				}
			}

			ImGui::PopID();
			if (col < 2) {
				ImGui::SameLine();
			}
		}
	}	
}

void Board::clearBoard() {
	gameState = GameState::Game_In_Progress; 
	markCount = 0;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			ImGui::PushID(buttons[row][col].id);       // unique ID for each button

			std::string buttonText;

			buttons[row][col].state = ButtonState::Empty; 
			buttons[row][col].text = ' ';

			ImGui::PopID();
		}
	}

}

void Board::handleButtonClick(int row, int col) {
	if (buttons[row][col].state == ButtonState::Empty) {
		if (markCount % 2 == 0) {					// even number is X's turn 
			buttons[row][col].state = ButtonState::X;
			buttons[row][col].text = 'X'; 
		}
		else {
			buttons[row][col].state = ButtonState::O;
			buttons[row][col].text = 'O';
		}
		markCount++;
	}
}

// check if someone has won depending on the mark given 
bool Board::checkWinner(char mark) {
	// check each row
	for (int row = 0; row < 3; row++) {
		int winCount = 0;

		for (int col = 0; col < 3; col++) {
			if (buttons[row][col].text[0] == mark) {
				winCount++;
			}
		}
		if (winCount == 3) {
			return true;
		}
	}

	// check each column
	int winCount = 0;
	for (int col = 0; col < 3; col++) {
		int winCount = 0;

		for (int row = 0; row < 3; row++) {
			if (buttons[row][col].text[0] == mark) {
				winCount++;
			}
		}
		if (winCount == 3) {
			return true;
		}
	}

	// check diagonal one way
	winCount = 0;
	for (int row = 0; row < 3; row++) {
		if (buttons[row][row].text[0] == mark) {
			winCount++;
		}

		if (winCount == 3) {
			return true;
		}
	}

	// check opposite diagonal
	for (int row = 2; row >= 0; row--) {
		int winCount = 0;
		if (buttons[row][2-row].text[0] == mark) {
			winCount++;
		}

		if (winCount == 3) {
			return true;
		}
	}
	return false;
}

bool Board::xWins() {
	if (checkWinner('X')) {
		gameState = GameState::Done; 
		return true;
	}
	return false; 
}

bool Board::oWins() {
	if (checkWinner('O')) {
		gameState = GameState::Done;
		return true;
	}
	return false;
}

bool Board::isFull() {
	if (markCount == 9) {
		gameState = GameState::Done;
	}
	return markCount == 9; 
}