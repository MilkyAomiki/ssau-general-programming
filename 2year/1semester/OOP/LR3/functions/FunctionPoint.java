package functions;

public class FunctionPoint
{
    private double x;
    private double y;

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    public FunctionPoint(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public FunctionPoint(FunctionPoint point) {
        x = point.x;
        y = point.y;
    }

    public FunctionPoint() {
        x = 0;
        y = 0;
    }
}