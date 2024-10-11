package functions;

public interface TabulatedFunction {
    void deletePoint(int index);
    void addPoint(FunctionPoint point)  throws InappropriateFunctionPointException;

    double getLeftDomainBorder();
    double getRightDomainBorder();

    int getPointsCount();

    FunctionPoint getPoint(int index);
    void setPoint(int index, FunctionPoint point)  throws InappropriateFunctionPointException;

    double getPointX(int index);
    void setPointX(int index, double x) throws InappropriateFunctionPointException;
    double getPointY(int index);
    void setPointY(int index, double y);

    double getFunctionValue(double x);
}
