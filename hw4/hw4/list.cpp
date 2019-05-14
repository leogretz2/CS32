void listAll(const MenuItem* m, string path) // two-parameter overload
{
	if (m->name() != "") {
		path += m->name();
		cout << path << endl;
	}
	if (m->menuItems() != nullptr) {
		if (m->name() != "")
			path += "/";
		for (vector<MenuItem*>::const_iterator p = m->menuItems()->begin(); p != m->menuItems()->end(); p++) {
			listAll(*p, path);
		}
	}
}