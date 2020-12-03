#include "stdafx.h"
#include "Tile.h"

#include "SpriteRenderer.h"
#include "Transform.h"

Tile::Tile(int x, int y, const std::string& path, bool isText) : pos(Vec2F(x, y)), path(path), isText(isText) {
	transform
		->SetScale(0.25f, 0.25f)
		->SetPos(Vec2F(x, y) * 1.13f / 4);
	AttachComponent<SpriteRenderer>()
		->SetTexture(path);
}

Tile::~Tile() {
}

void Tile::OnUpdate() {
	transform
		->SetPos(pos * 1.13f / 4);
}

Tile* Tile::SetX(int x) {
	this->pos.x = x;

	return this;
}

Tile* Tile::SetY(int y) {
	this->pos.y = y;

	return this;
}

Tile* Tile::SetPos(Vec2F pos) {
	this->pos = pos;

	return this;
}

Tile* Tile::SetPos(int x, int y) {
	this->pos = Vec2F(x, y);

	return this;
}

Tile* Tile::SetIsText(bool isText) {
	this->isText = isText;

	return this;
}

Tile* Tile::Translate(Vec2F pos)
{
	this->pos += pos;

	return this;
}

Tile* Tile::Translate(int x, int y)
{
	this->pos += Vec2F(x, y);

	return this;
}

Vec2F Tile::GetPos() {
	return pos;
}

std::string Tile::GetPath()
{
	return path;
}

bool Tile::GetIsText() {
	return isText;
}