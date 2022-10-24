#include <gsl/pointers>
#include <gsl/span>
#include <iostream>
#include <memory>
#include <gsl/gsl>
#include <stdlib.h>
#include <concepts>
#include <type_traits>
#include <vector>

using namespace std;

//	forward
//	https://en.cppreference.com/w/cpp/utility/forward

class Object 
{
public:
	virtual ~Object(){}

	virtual void Update() = 0;
};

template<typename T>
concept LimitType = std::is_same_v<T, int> || std::is_same_v<T, double>;

template<LimitType T>
class Enemy : public Object
{
public:
	Enemy(T damage, T hp)
	{
		Damage = std::make_shared<T>(damage);
		HP = std::make_shared<T>(hp);
	}

	T GetDamage() const
	{
		return *Damage.get();
	}
	
	T GetHP() const
	{
		return *HP.get();
	}

	void Update() override
	{
		std::string type_ = "int";

		if(std::is_same_v<T, double> == true) 
		{
			type_ = "double";
		}

		std::cout << type_ << " Enemy = " << "Damage : " << *Damage.get() << " HP : " << *HP.get() << "\n";
	}

private:
	std::shared_ptr<T> Damage;
	std::shared_ptr<T> HP;
};

class EnemyManager
{
public:
EnemyManager() = default;
EnemyManager(const EnemyManager&) = delete;
EnemyManager(EnemyManager&&) = delete;

EnemyManager& operator=(const EnemyManager&) = delete;
EnemyManager& operator=(EnemyManager&&) = delete;

~EnemyManager()
{
	for(Object* obj : Objects)
	{
		delete obj;
	}
}

template<LimitType T, template<typename> class Obj>
void AddObject(Obj<T>* value)
{
	Objects.push_back(value);
}

template<LimitType T, template<typename> class Obj, typename... Args>
void AddObject(Obj<T>* value, Args... args)
{
	Objects.push_back(value);

	AddObject(args...);
}

void Update()
{
	for(Object* obj : Objects)
	{
		obj->Update();
	}
}

private:
	std::vector<Object*> Objects;
};

template<LimitType T>
void CoutEnemy(Enemy<T>* obj)
{
	std::cout << "Damage : " << obj->GetDamage() << ", HP : " << obj->GetHP() << "\n";
}

template<LimitType T>
requires LimitType<T>
void CoutValue(gsl::span<T> span_)
{
	for(T value : span_)
	{
		std:: cout << value << " ";
	}

	std::cout << "\n";
}

int main()
{
	gsl::owner<Enemy<int>*> enemy = new Enemy{1, 10};
	
	std::cout << enemy->GetDamage() << " " << enemy->GetHP() << "\n";

	delete enemy;

	EnemyManager mManager;

	mManager.AddObject(new Enemy<int>{1, 10});
	mManager.AddObject(new Enemy<double>{56.25, 1.47});
	mManager.AddObject(new Enemy<double>{1.1, 11.1});
	mManager.AddObject(new Enemy<int>{19, 23});

	mManager.AddObject(new Enemy<int>{1, 100}, new Enemy<double>{132, 129}, new Enemy<int>{1, 100}, new Enemy<int>{1, 100});

	mManager.Update();

	std::vector<int> intArrays{1, 2, 3, 4, 5};
	std::vector<double> doubleArrays{1.1, 2.2, 3.3, 4.4, 5.5};

	gsl::span<int> spans_int{intArrays};
	gsl::span<double> spans_double{doubleArrays};

	std::cout << std::boolalpha;
	std::cout << std::is_constructible<Enemy<double>, int, float>::value << "\n";

	CoutValue(spans_int);
	CoutValue(spans_double);

	return 0; 
}
