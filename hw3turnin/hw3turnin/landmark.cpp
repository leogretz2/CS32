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