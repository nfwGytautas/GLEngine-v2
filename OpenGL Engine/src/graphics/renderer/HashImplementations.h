#pragma once

class Model;

class KeyHasher
{
public:
	size_t operator()(const Model& model) const;
};