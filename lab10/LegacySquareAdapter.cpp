//lab 10 resizing shapes
//Jerry Zheng

#include <iostream>

using std::cout; using std::endl; using std::cin;

// base interface
class Figure {
public:
	virtual void draw() = 0;
	virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	void oldDraw() {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}
	void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
		topLeftX_ = topLeftX;
		topLeftY_ = topLeftY;
		bottomRightX_ = bottomRightX;
		bottomRightY_ = bottomRightY;
	}
	int getTopleftX() { return topLeftX_; }
	int getTopLeftY() { return topLeftY_; }
	int getBottomRightX() { return bottomRightX_; }
	int getBottomRightY() { return bottomRightY_; }
	// defining top/left and bottom/right coordinates 
private:
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
	private LegacyRectangle {
public:
	SquareAdapter(int size) :
		LegacyRectangle(0, 0, size, size) {};
	void draw() override {
		oldDraw();
	}
	//returns the size
	int size() { return getBottomRightX(); }

	//using the move pointer to point to move to resize with new parameters
	void resize(int newSize) { this->move(0, 0, newSize, newSize); }
};


int main() {
	//user enters a size
	int size;
	cout << "Enter a size for your square";
	cin >> size;
	SquareAdapter* square = new SquareAdapter(size);
	square->draw();
	cout << endl;
	cout << "The size of your square is " << square->size();

	//promts user to enter new size for resizing
	int resize;
	cout << endl;
	cout << "Time to Resize: Enter size for your new square";
	cin >> resize;
	cout << endl;
	square->resize(resize);
	square->draw();
	cout << "The new size of your square is " << square->size() << endl;

}
	