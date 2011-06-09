/*
slowmoVideo creates slow-motion videos from normal-speed videos.
Copyright (C) 2011  Simon A. Eugster (Granjow)  <simon.eu@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/


class QImage;
class FlowField_sV;

/**
  Provides interpolation methods between frames
  */
class Interpolate_sV {

 public:

    struct Movement {
	float moveX;
	float moveY;
    };

    static void forwardFlow(const QImage& left, const FlowField_sV *flow, float pos, QImage& output);
    static void twowayFlow(const QImage& left, const QImage& right, const FlowField_sV *flowForward, const FlowField_sV *flowBackward, float pos, QImage& output);
};
