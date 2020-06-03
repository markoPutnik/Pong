#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine_2.0.h"

using namespace std;
using namespace olc;

class Pong : public PixelGameEngine {

public:

	Pong() {
		sAppName = "PONG GAME";
	}

private:

	Sprite *wallSprite = nullptr;
	Decal *wallDecOne = nullptr;
	Decal *wallDecTwo = nullptr;

	Sprite *ballSprite = nullptr;
	Decal *ballDec = nullptr;

	int m_nScoreOne, m_nScoreTwo;

	float fDecOneY, fDecOneX;
	float fDecTwoY, fDecTwoX;

	float fBallX, fBallY;

public:

	bool OnUserCreate() override{

		m_nScoreOne = 0;
		m_nScoreTwo = 0;

		wallSprite = new Sprite("assets/wall.png");
		wallDecOne = new Decal(wallSprite);
		wallDecTwo = new Decal(wallSprite);

		ballSprite = new Sprite("assets/ball.png");
		ballDec = new Decal(ballSprite);

		fDecOneX = -1.0f;
		fDecTwoX = ScreenWidth() - 10.0f;

		fDecOneY = ScreenHeight() / 3.0f;
		fDecTwoY = ScreenHeight() / 3.0f;

		fBallX = 20.0f;
		fBallY = ScreenHeight() / 2.0f;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override{


		// Clearthe screen
		Clear(DARK_BLUE);

		// Calculating input for player one
		if (GetKey(Key::UP).bHeld && fDecTwoY > 0.0f) {

			fDecTwoY -= 0.02f;

		}
		else if (GetKey(Key::DOWN).bHeld && fDecTwoY < ScreenHeight() - 35.0f) {

			fDecTwoY += 0.02f;

		}

		// Calculating input for player two
		if (GetKey(Key::W).bHeld && fDecOneY > 0.0f) {

			fDecOneY -= 0.02f;

		}
		else if (GetKey(Key::S).bHeld && fDecOneY < ScreenHeight() - 35.0f) {

			fDecOneY += 0.02f;

		}


		// Drawing the score
		DrawString({ ScreenWidth() / 2 - 7, 5 }, to_string(m_nScoreOne), WHITE);
		DrawString({ ScreenWidth() / 2 + 7, 5 }, to_string(m_nScoreTwo), WHITE);


		// Drawing our decals
		DrawDecal({ fDecOneX, fDecOneY }, wallDecOne, { 0.1f, 0.1f });
		DrawDecal({ fDecTwoX, fDecTwoY }, wallDecTwo, { 0.1f, 0.1f });

		return true;
	}

};

int main() {

	Pong pong;
	if (pong.Construct(160, 120, 5, 5)) {
		pong.Start();
	}

	system("pause");
	return 0;
}