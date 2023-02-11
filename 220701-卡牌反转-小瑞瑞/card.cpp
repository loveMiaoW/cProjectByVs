#include "card.h"
card::card(int x, int y, string imgURL, string imgyURL)
{
	this->x = x;
	this->y = y;
	this->start = card::cardStart::close;
	this->imgURL = imgURL;
	this->imgyURL = imgyURL;
	img = new IMAGE[2];
	loadimage(img, imgyURL.c_str(), width, height);
	loadimage(img + 1, imgURL.c_str(), width, height);
}
void card::setStart(cardStart state)
{
	this->start = state;
}

string card::getURL()
{
	return imgURL;
}

bool card::mouseInCard(ExMessage msg)
{
	if ((this->start != card::cardStart::no && this->start != card::cardStart::open) && (msg.x >= this->x && msg.x <= this->x + this->width) && (msg.y >= this->y && msg.y <= this->y + this->height)) {
		return true;
	}
	return false;
}

bool card::clickCard(ExMessage msg)
{
	if (this->start != card::cardStart::no && mouseInCard(msg) && msg.message == WM_LBUTTONDOWN) {
		this->start = card::cardStart::open;
		return true;
	}
	return false;
}

void card::show()
{
	switch (this->start) {
	case card::cardStart::close:
		putimage(x, y, img);
		break;
	case card::cardStart::open :
		putimage(x, y, img + 1);
		break;
	case card::cardStart::no:
		break;
	}
}
