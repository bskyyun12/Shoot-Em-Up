#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H
#include "MathHelper.h"

class GameEntity
{
public:

	enum SPACE
	{
		local = 0,
		world = 1
	};

private:
	Vector2D mPos;
	float mRotation;
	Vector2D mScale;

	bool mActive;

	GameEntity* mParent = nullptr;

public:

	GameEntity(Vector2D pos = VECTOR2D_ZERO);
	~GameEntity();

	//------------------------------------------------------------------------------------------
	//Sets the GameEntity's position, it only updates local space                               
	//If the object has a parent, its new position is relative to the parent's world position   
	//If the object has no parent, its new position is relative to the origin                   
	//------------------------------------------------------------------------------------------
	void Pos(Vector2D pos);
	//----------------------------------------------------------------------------------------------------------------
	//Returns the position of the GameEntity                                                                          
	//If space = world, the world position is returned (relative to the origin)                                       
	//if space = local, if the object has a parent, the local position is returned (relative to the parent position)  
	//       otherwise if the object has no parent, the world position is returned instead (relative to the origin)   
	//----------------------------------------------------------------------------------------------------------------
	Vector2D Pos(SPACE space = world);

	//------------------------------------------------------------------------------------------
	//Sets the GameEntity's rotation, it only updates local space                               
	//If the object has a parent, its new rotation is relative to the parent's world rotation   
	//If the object has no parent, its new rotation is set to the given rotation                
	//------------------------------------------------------------------------------------------
	void Rotation(float rotation);
	//-----------------------------------------------------------------------------------------------------------------
	//Returns the rotation of the GameEntity                                                                           
	//If space = world, the world rotation is returned (total rotation of parent[if it has one] and object)            
	//if space = local, if the object has a parent, the local rotation is returned (relative to the parent's rotation) 
	//       otherwise if the object has no parent, the world rotation is returned instead (relative to the origim)    
	//-----------------------------------------------------------------------------------------------------------------
	float Rotation(SPACE space = world);

	//------------------------------------------------------------
	//Sets the GameEntity's scale, it only updates local space    
	//------------------------------------------------------------
	void Scale(Vector2D scale);
	//-----------------------------------------------------------------------------------------------------------------
	//Returns the scale of the GameEntity                                                                              
	//If space = world, the world scale is returned (product of the parent and local scale)                            
	//if space = local, if the object has a parent, the local scale is returned (relative to the parent's scale)       
	//       otherwise if the object has no parent, the GameEntity's scale is returned instead                         
	//-----------------------------------------------------------------------------------------------------------------
	Vector2D Scale(SPACE space = world);

	//--------------------------------------------
	//Sets the active state of the GameEntity     
	//--------------------------------------------
	void Active(bool active);
	//--------------------------------------------
	//Returns the active state of the GameEntity  
	//--------------------------------------------
	bool Active();

	//--------------------------------------------------------------------------------------------------------------------------
	//Sets the parent of the GameEnity as the given GameEntity                                                                  
	//If the GameEntity has no parent, the given GameEntity is set as its parent                                                
	//If the GameEntity has a parent, the given game entity is set as the new parent,                                           
	//       and the lcoal Position/Rotation/Scale are changed to be relative to the new parent (world values are unchanged)    
	//If NULL is passed in, the GameEntity is considered without a parent,                                                      
	//       and all values are set to be relative to the origin (world values are unchanged)                                   
	//--------------------------------------------------------------------------------------------------------------------------
	void Parent(GameEntity* parent);
	//-----------------------------------------------
	//Returns the Current parent of the GameEntity,  
	//Returns NULL if the GameEntity has no parent   
	//-----------------------------------------------
	GameEntity* Parent();

	//---------------------------------------------------------------
	//Translates the GameEntity's lcoal position by the given amount 
	//---------------------------------------------------------------
	void Translate(Vector2D vec);
	//------------------------------------------------------
	//Rotates the GameEntity's locally by the given amount  
	//------------------------------------------------------
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();

};

#endif // !_GAMEENTITY_H
