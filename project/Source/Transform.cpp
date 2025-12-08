#include "transform.h"
#include <assert.h>

Transform::Transform() :
	Transform(V3::ZERO, V3::ZERO, V3::ONE)
{
}

Transform::Transform(const Vector3& _position) : 
	Transform(_position, V3::ZERO, V3::ONE)
{
}

Transform::Transform(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale) :
	Transform(_position, _rotation, _scale, nullptr)
{
}

Transform::Transform(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale, Transform* _parent) :
	position(_position),
	rotation(_rotation),
	scale(_scale),
	parent(nullptr)
{
	SetParent(_parent);
}

Transform::~Transform()
{
	// 親と縁を切る
	if (parent != nullptr)
	{
		parent->RemoveChild(this);
		parent = nullptr;
	}

	// 子と縁を切る
	for (Transform* c : children)
	{
		c->RemoveParent(this, false);
	}
}

const Transform Transform::Global() const
{
	// 自分の情報(相対的)
	Vector3 globalPosition = position;
	Vector3 globalRotation = rotation;
	Vector3 globalScale = scale;

	// 親を持つ場合
	if (parent != nullptr)
	{
		globalPosition = VTransform(position, parent->Global().Matrix());
		globalRotation += parent->Global().rotation;
		globalScale *= parent->Global().scale;
	}

	return Transform(globalPosition, globalRotation, globalScale);
}

const MATRIX Transform::Matrix() const
{
	MATRIX matrix = MGetIdent();
	matrix = MMult(matrix, MGetScale(scale));
	matrix = MMult(matrix, RotationMatrix());
	matrix = MMult(matrix, MGetTranslate(position));
	return matrix;
}

const MATRIX Transform::RotationMatrix() const
{
	MATRIX matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotZ(rotation.z));
	matrix = MMult(matrix, MGetRotX(rotation.x));
	matrix = MMult(matrix, MGetRotY(rotation.y));
	return matrix;
}

const Vector3 Transform::Right() const
{
	Vector3 vec = Vector3(1, 0, 0);
	vec = VTransform(vec, RotationMatrix());
	return vec;
}

const Vector3 Transform::Up() const
{
	Vector3 vec = Vector3(0, 1, 0);
	vec = VTransform(vec, RotationMatrix());
	return vec;
}

const Vector3 Transform::Forward() const
{
	Vector3 vec = Vector3(0, 0, 1);
	vec = VTransform(vec, RotationMatrix());
	return vec;
}

const Vector3 Transform::LimitedRotation() const
{
	Vector3 limitedRot = V3::ZERO;

	// x,y,zそれぞれ計算
	for (int i = 0; i < 3; i++)
	{
		float angle = rotation.Get(i);

		// 0より小さい場合、2π(一周)足し続ける
		while (angle < 0)
		{
			angle += DX_PI_F * 2;
		}
		// 2π以上の場合、2π(一周)引き続ける
		while (angle >= DX_PI_F * 2)
		{
			angle -= DX_PI_F * 2;
		}

		limitedRot.Set(i, angle);
	}

	return limitedRot;
}

const std::string Transform::ToString() const
{
	std::string ret;

	ret += position.ToString() + ",";
	ret += rotation.ToString() + ",";
	ret += scale.ToString();

	return ret;
}

void Transform::SetParent(Transform* _parent)
{
	if (parent != nullptr)
	{
		RemoveParent(parent);
	}

	parent = _parent;

	if (parent != nullptr)
		parent->AddChild(this);
}

void Transform::SetGlobal(const Transform& global)
{
	if (parent == nullptr)
	{
		position = global.position;
		rotation = global.rotation;
		scale = global.scale;
		return;
	}

	this->position -= parent->Global().position;
	MATRIX mRot = MGetIdent();
	mRot = MMult(mRot, MGetRotZ(-parent->Global().rotation.z));
	mRot = MMult(mRot, MGetRotX(-parent->Global().rotation.x));
	mRot = MMult(mRot, MGetRotY(-parent->Global().rotation.y));
	this->position = this->position.Transform(mRot);
	this->position.x /= parent->Global().scale.x;
	this->position.y /= parent->Global().scale.y;
	this->position.z /= parent->Global().scale.z;
	this->rotation -= parent->Global().rotation;
	this->scale /= parent->Global().scale;
}

const Transform Transform::operator+(const Transform& trs) const
{
	Transform ans = *this;

	ans.position = position + trs.position;
	ans.rotation = rotation + trs.rotation;
	ans.scale = scale + trs.scale;

	return ans;
}

const Transform Transform::operator-(const Transform& trs) const
{
	Transform ans;

	ans.position = position - trs.position;
	ans.rotation = rotation - trs.rotation;
	ans.scale = scale - trs.scale;

	return ans;
}

const Transform Transform::operator*(const float sca) const
{
	Transform ans;

	ans.position = position * sca;
	ans.rotation = rotation * sca;
	ans.scale = scale * sca;

	return ans;
}

const Transform Transform::operator/(const float sca) const
{
	Transform ans;

	ans.position = position / sca;
	ans.rotation = rotation / sca;
	ans.scale = scale / sca;

	return ans;
}

const Transform Transform::operator-() const
{
	Transform ans = *this;

	ans *= -1.0f;

	return ans;
}

void Transform::operator+=(const Transform& trs)
{
	position = position + trs.position;
	rotation = rotation + trs.rotation;
	scale = scale + trs.scale;
}

void Transform::operator-=(const Transform& trs)
{
	position = position - trs.position;
	rotation = rotation - trs.rotation;
	scale = scale - trs.scale;
}

void Transform::operator*=(const float sca)
{
	position = position * sca;
	rotation = rotation * sca;
	scale = scale * sca;
}

void Transform::RemoveChild(Transform* child)
{
	for (auto itr = children.begin(); itr != children.end(); itr++)
	{
		if (*itr == child)
		{
			children.erase(itr);
			return;
		}
	}
}

void Transform::RemoveParent(Transform* _parent, bool removeFromChildren)
{
	// 親がnullptrならスキップ
	if (parent == nullptr) return;
	// 親以外には操作できない
	if (parent != _parent) return;

	// 座標が移動しないように
	const Transform globalTransform = this->Global();
	this->position = globalTransform.position;
	this->rotation = globalTransform.rotation;
	this->scale = globalTransform.scale;

	// 繋がりを断つ
	if (removeFromChildren)
		parent->RemoveChild(this);
	parent = nullptr;
}
