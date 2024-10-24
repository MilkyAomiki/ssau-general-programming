package functions;

import java.io.Externalizable;

public interface TabulatedFunction extends Function{
    void deletePoint(int index);
    void addPoint(FunctionPoint point)  throws InappropriateFunctionPointException;

    int getPointsCount();

    FunctionPoint getPoint(int index);
    void setPoint(int index, FunctionPoint point)  throws InappropriateFunctionPointException;

    double getPointX(int index);
    void setPointX(int index, double x) throws InappropriateFunctionPointException;
    double getPointY(int index);
    void setPointY(int index, double y);
}
