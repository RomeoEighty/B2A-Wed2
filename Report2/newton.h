#ifndef NEWTON_H
#define NEWTON_H

double isConvex(double x, Node *node);
double calculateXAtNodeBecomesExtreme(Node *node);
double calculateXAtNodeBecomesExtremeFrom(Node *node, double initVal);

#endif
