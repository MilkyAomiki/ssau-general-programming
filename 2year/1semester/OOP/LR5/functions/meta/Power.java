package functions.meta;

import functions.Function;

public class Power implements Function {
    private Function base;
    private double power;

    public Power(Function base, double power) {
        this.base = base;
        this.power = power;
    }

    @Override
    public double getLeftDomainBorder() {
        return base.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder() {
        return base.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x) {
        return Math.pow(base.getFunctionValue(x), power);
    }
}
