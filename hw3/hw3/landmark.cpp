#include <iostream>
#include <string>
using namespace std;

class Landmark {
public :
	Landmark(const string name) : m_name(name) {}
	virtual ~Landmark() {}
	virtual string name() const { return m_name; }
	virtual string color() const /*{ return m_color; }*/ = 0;
	virtual string icon() const /*{ return m_icon; }*/ = 0;

private:
	string m_name;
	/*string m_color;
	string m_icon;*/
};

class Hotel : public Landmark {
public:
	Hotel(const string name) : Landmark(name), m_color("yellow"), m_icon("bed") {}
	virtual ~Hotel(){
		cout << "Destroying the hotel " + name() << endl;
	}
	virtual string name() const { return Landmark::name(); }
	virtual string color() const { return /*Landmark::color();*/ m_color; }
	virtual string icon() const { return /*Landmark::icon(); */ m_icon; }
private:
	string m_color;
	string m_icon;

};

class Restaurant : public Landmark {
public:
	Restaurant(const string name, const int capacity) : Landmark(name), m_capacity(capacity), m_color("yellow") {
		if (capacity < 40)
			m_icon = "small knife/fork";
		else
			m_icon = "large knife/fork";
	}
	virtual ~Restaurant() {
		cout << "Destroying the restaurant " + name() << endl;

	}
	virtual string name() const { return Landmark::name(); }
	virtual string color() const { return /*Landmark::color();*/ m_color;}
	virtual string icon() const { return /*Landmark::icon();*/ m_icon; }
private:
	int m_capacity;
	string m_color;
	string m_icon;
};

class Hospital : public Landmark {
public:
	Hospital(const string name) : Landmark(name), m_color("blue"), m_icon("H") {}
	virtual ~Hospital() {
		cout << "Destroying the hospital " + name() << endl;

	}
	virtual string name() const { return Landmark::name(); }
	virtual string color() const { return /*Landmark::color();*/ m_color;}
	virtual string icon() const { return /*Landmark::icon();*/ m_icon; }
private:
	string m_color;
	string m_icon;
};




void display(const Landmark* lm)
{
	cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
		<< lm->name() << "." << endl;
}

//int main()
//{
//	Landmark* landmarks[4];
//	landmarks[0] = new Hotel("Westwood Rest Good");
//	// Restaurants have a name and seating capacity.  Restaurants with a
//	// capacity under 40 have a small knife/fork icon; those with a capacity
//	// 40 or over have a large knife/fork icon.
//	landmarks[1] = new Restaurant("Bruin Bite", 30);
//	landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
//	landmarks[3] = new Hospital("UCLA Medical Center");
//
//	cout << "Here are the landmarks." << endl;
//	for (int k = 0; k < 4; k++)
//		display(landmarks[k]);
//
//	// Clean up the landmarks before exiting
//	cout << "Cleaning up." << endl;
//	for (int k = 0; k < 4; k++)
//		delete landmarks[k];
//}