// -*- mode: c++ -*-
// Copyright (c) 2009 Olaf Dietsche

#include "framesequence.h"
#include <sstream>
#include <qlayout.h>
#include <qpushbutton.h>
#include "imageprovider.h"
#include "dvbcut.h"

void frame::gotoFrame()
{
	dvbcut_->gotoFrame(frameno_);
}

framesequence::framesequence(QWidget *parent, int nframes, dvbcut *main, imageprovider *imgp)
	: layout_(0),
	  imgp_(imgp),
	  distance_(1500)
{
	createWidgets(parent, nframes, main);
}

framesequence::~framesequence()
{
	for (std::vector<frame*>::iterator i = frames_.begin(); i != frames_.end(); ++i)
		delete *i;

	frames_.clear();
	delete imgp_;
// FIXME	delete layout_;
}

void framesequence::imgp(imageprovider *imgp)
{
	delete imgp_;
	imgp_ = imgp;
}

void framesequence::update(int frameno)
{
	if (!imgp_)
		return;

	bool decodeallgop = distance_ == 1;
	int n = frames_.size();
	frameno -= n / 2 * distance_;
	if (frameno < 0)
		frameno = 0;

	for (std::vector<frame*>::iterator i = frames_.begin(); i != frames_.end(); ++i, frameno += distance_) {
		QPixmap px = imgp_->getimage(frameno, decodeallgop);
		if (px.isNull()) {
			(*i)->image_->hide();
		} else {
			(*i)->frameno_ = frameno;
			(*i)->image_->show();
			(*i)->image_->setMinimumSize(px.size());
			(*i)->image_->setPixmap(px);
		}
	}
}

void framesequence::createWidgets(QWidget *parent, int nframes, dvbcut *main)
{
	layout_ = new QHBoxLayout(-1, "framesequence");
	for (int i = 0; i < nframes; ++i) {
		QPushButton *w = new QPushButton(parent);
		w->setFlat(true);
		layout_->addWidget(w);
		frame *f = new frame();
		f->image_ = w;
		f->dvbcut_ = main;
		frames_.push_back(f);
		QObject::connect(w, SIGNAL(clicked()), f, SLOT(gotoFrame()));
		w->hide();
	}

	QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout_->addItem(spacer);
}
