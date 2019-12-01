#pragma warning( push )
#pragma warning (disable : 4244 )
#pragma warning (disable : 26451 )

#include "Boxxy.h"

Boxxy::Boxxy(int index, int path, bool challengeStage)
	:Enemy(index, path, challengeStage)
{
	if (!challengeStage)
	{
		mTargetPosition = FormationPosition();
	}
	mTexture = new Texture("idle.png");
	mTexture->Parent(this);
	mTexture->Pos(VECTOR2D_ZERO);
}

Boxxy::~Boxxy(){

}

Vector2D Boxxy::FormationPosition()
{
	Vector2D retVal;

	retVal.y = (sFormation->GridSize().y + sFormation->GridSize().y * 2 * (mIndex / 8)) * pow(-1, static_cast<int64_t>(mIndex) % 2 + 1);
	retVal.x = sFormation->GridSize().x * ((mIndex % 8) / 2);

	return retVal;
}

void Boxxy::HandleDiveState()
{


}

void Boxxy::HandleDeadState()
{

}
#pragma warning( pop )