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
	int m_nOverallScore;

	int nDirection;

	float fDecOneY, fDecOneX;
	float fDecTwoY, fDecTwoX;

	float fBallX, fBallY;
	float fBallDX, fBallDY;
	float fAngle;
	float fOldBallX, fOldBallY;

	bool bCollisionWallOne, bCollisionWallTwo;
	bool bScoreCounter;

	bool scoreCounter;

public:

	bool OnUserCreate() override{

		m_nScoreOne = 0;
		m_nScoreTwo = 0;
		m_nOverallScore = 0;

		nDirection = 1;

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

		fAngle = 0.1f;
		fBallDX = cosf(fAngle);
		fBallDY = sinf(fAngle);

		bCollisionWallOne = true;
		bCollisionWallTwo = false;

		bScoreCounter = true;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override{


		float fSpeed = 0.02f;

		// Clearthe screen
		Clear(DARK_BLUE);

		// Calculating input for player two
		if (GetKey(Key::UP).bHeld && fDecTwoY > 0.0f) {

			fDecTwoY -= 0.02f;

		}
		else if (GetKey(Key::DOWN).bHeld && fDecTwoY < ScreenHeight() - 35.0f) {

			fDecTwoY += 0.02f;

		}

		// Calculating input for player one
		if (GetKey(Key::W).bHeld && fDecOneY > 0.0f) {

			fDecOneY -= 0.02f;

		}
		else if (GetKey(Key::S).bHeld && fDecOneY < ScreenHeight() - 35.0f) {

			fDecOneY += 0.02f;

		}


		// Updating ball position
		
		fOldBallX = fBallX;
		fOldBallY = fBallY;

		fBallX += fBallDX*fSpeed*nDirection;
		fBallY += fBallDY*fSpeed*nDirection;


		// Checking ball position for wall one
		if (fBallX > fDecOneX && fBallX < fDecOneX + 10.0f && fBallY > fDecOneY && fBallY < 2 * fDecOneY + 10.0f) {

			if ((int)fBallX != (int)fOldBallX) {
				fBallDX *= -1;
			}
			if ((int)fBallY != (int)fOldBallY) {
				fBallDY *= -1;
			}

		}
		else if (fBallX > fDecOneX && fBallX < fDecOneX + 10.0f && bScoreCounter) {

			m_nScoreOne++;
			m_nOverallScore++;

			bScoreCounter = false;

			fBallX = 20.0f;
			fBallY = ScreenHeight() / 2.0f;

			nDirection = 1;

		}

		// Checking ball position for wall two
		if (fBallX > fDecTwoX - 5.0f && fBallX < fDecTwoX + 10.0f && fBallY > fDecTwoY && fBallY < 2 * fDecTwoY - 5.0f) {

			if ((int)fBallX != (int)fOldBallX) {
				fBallDX *= -1;
			}
			if ((int)fBallY != (int)fOldBallY) {
				fBallDY *= -1;
			}

		}
		else if (fBallX > fDecTwoX && fBallX < fDecTwoX + 10.0f && bScoreCounter) {

			m_nScoreTwo++;
			m_nOverallScore++;

			bScoreCounter = false;

			fBallX = ScreenWidth() - 10.0f;
			fBallY = ScreenHeight() / 2.0f;

			nDirection = -1;

		}

		// Checking ball position against walls

		if (fBallY < 0) {
			fBallDY *= -1;
		}
		else if (fBallY > ScreenHeight() - 7.0f) {
			fBallDY *= -1;
		}


		// Drawing the score
		DrawString({ ScreenWidth() / 2 - 7, 5 }, to_string(m_nScoreOne), WHITE);
		DrawString({ ScreenWidth() / 2 + 7, 5 }, to_string(m_nScoreTwo), WHITE);


		// Drawing our wall decals
		DrawDecal({ fDecOneX, fDecOneY }, wallDecOne, { 0.1f, 0.1f });
		DrawDecal({ fDecTwoX, fDecTwoY }, wallDecTwo, { 0.1f, 0.1f });


		// Drawing ball decal
		DrawDecal({ fBallX, fBallY }, ballDec, { 0.02f, 0.02f });


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