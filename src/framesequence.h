#ifndef __framesequence_h_included__
#define __framesequence_h_included__

// -*- mode: c++ -*-
// Copyright (c) 2009 Olaf Dietsche

#include <vector>
#include <qobject.h>
class QBoxLayout;
class QPushButton;
class QWidget;
class dvbcut;
class imageprovider;

class frame : public QObject {
	Q_OBJECT
public:
	QPushButton *image_;
	int frameno_;
	dvbcut *dvbcut_;
public slots:
	void gotoFrame();
};

class framesequence {
public:
	framesequence(QWidget *parent, int nframes, dvbcut *main, imageprovider *imgp = 0);
	virtual ~framesequence();

	QBoxLayout *layout() const { return layout_; }
	imageprovider *imgp() const { return imgp_; }
	void imgp(imageprovider *imgp);
	void distance(int distance) { distance_ = distance; }
	void update(int frameno);

private:
	framesequence(const framesequence&);
	framesequence& operator=(const framesequence&);

	void createWidgets(QWidget *parent, int nframes, dvbcut *main);

	QBoxLayout *layout_;
	std::vector<frame*> frames_;
	imageprovider *imgp_;
	int distance_;
};

#endif
