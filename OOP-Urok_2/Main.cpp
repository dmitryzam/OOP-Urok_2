#include<iostream>

// Урок 2. Инкапсуляция, Агрегация и Композиция (Урок 1 - был теоретическим)

class NameOfClass;	// - объявление класса
// ВСЕ ЧЛЕНЫ КЛАССА ИМЕЮТ ДОСТУП, НЕВАЖНО ГДЕ ОНИ НАХОДЯТСЯ (В КОНЦЕ ИЛИ В НАЧАЛЕ)
class NameOfClass {
	// внутренности фигурных скобок - тедо класса.
	// тут хранятся свойства и поведения объектов

	// хранящиеся здесь элементы доступны всем клиентам класса
	// Наследникам класса, и клиентам наследника.
public:
	// обычно в этой зоне оставляют только методы класса

	NameOfClass() {	// - конструктор
		SetEven(2);	// - заполнить по умолчанию двойкой
		even_ = 2;
	}

	// конструктор применил делегацию работы
	// для передачи прав на создание и заполнение своего поля
	// конструктору поля
	NameOfClass(int newNum):even_(newNum)	// - делегация, чтобы можно было инициализировать obj2 (см. строку 70) 
	{
		if (even_ % 2 == 1) {
			throw 1;
		}	
	}
	// делегация на поля применяются для возможности работы с универсальной
	// инициализацией чере {} и является единственным способом заполнить
	// поля, которые являются ссылками и неинициализированными константами.
	
	void SomeWork() {
		std::cout << "I'n alive!\n";
	}
	int GetEven() {		// - метод ацессор (геттер) для доступа к приватному even_
		return even_;
	}
	void SetEven(int newNum) {	// - сеттер
		if (newNum % 2 == 0) {
			even_ = newNum;
		}
		else {
			throw 1;	// - возврат 1, если введено было нечетное число
		}
	}

	// хранящиеся здесь элементы доступны только членам класса,
	// дружественным классам и функциям
private:
	int even_;

	// хранящиеся здесь элементы доступны только членам класса,
	// дружественным классам и функциям и членам классов наследников
protected:



};	// - определение класса

int main() {

	NameOfClass obj; // -создали экземпляр класса с именем obj
	obj.SomeWork();
	//obj.even_ = 8; - не имеем доступ к полю even_
	obj.SetEven(8);
	std::cout << obj.GetEven() << '\n';

	NameOfClass obj2{10};	// инийиализировали объект сразу
	std::cout << obj2.GetEven() << '\n';
	obj2.SetEven(4);
	std::cout << obj2.GetEven() << '\n';


	return 0;
}

class Day {
public:
	Day() :units_(0) {}
	Day(int days):units_(days){
	{
		if (units_ < 0)
			throw 1;
		}
	}

	int Days() {
		return units_;
	}

	void Days(const Day& obj) {
		this->units_ = obj.units_;
	}

	void AddDays(const Day& obj) {
		this->units_ += obj.units_;
	}


private:
	int units_;
};

class Month {
public:
	Month():units_(0){}
	Month(int months) :units_(months) {
		if (units_ < 0) {
			throw 1;
		}
	}
	Month(Day days) {
		units_ = days.Days()/30;
	}
	int Months() {
		return units_;
	}

	void Months(const Month& obj) {
		units_ = obj.units_;
	}
	void AddMonths(const Month& obj) {
		units_ += obj.units_;
	}

private:
	int units_;
};

class Year {
public:
	Year() :units_(0) {}
	Year(int year) :units_(year) {
		if (units_ < 0) {
			throw 1;
		}
	}
	Year(Day days) {
		units_ = days.Days() / 365;
	}
	Year(Month months) {
		units_ = months.Months() / 12;
	}
	int Years() {
		return units_;
	}

	void Years(const Year& obj) {
		units_ = obj.units_;
	}
	void AddYears(const Year& obj) {
		units_ += obj.units_;
	}

private:
	int units_;
};

class Date {
public:
	// тут будут правила класса - даты


private:	// этот класс собирает поля на правах композиции
	Day day_;
	Month month_;
	Year year_;
};	// данный класс собирает внутри себя объекты других классов на правах
	// композиции. Композиция - это такой способ формирования при которо внешний 
	// объект несет ответственность во время жизни вложенных компонентов.


// Композиция - способ связи полей класса с его объектом при котором поле
// является неотъемлимой частью объекта без которого невозможна работа.
// При композиции объект в который сложены композиционные поля несет ответственность
// за время жизни этих поле.

// Агрегация - способ связи полей класса с его объектом при котором поле
// является легко заменяемой частью класса. Отсутствие агрегационного
// компонента не ведет к проблемам в жизненном цикле хранящего данное поле объекта.
// При агрегации хранящий объект не несет ответственности за время жизни
// хранимого на правах агрегации поля
