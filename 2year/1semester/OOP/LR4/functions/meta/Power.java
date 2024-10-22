package functions.meta;

import functions.Function;

public class Power implements Function {
    private Function base;
    private Function power;

    public Power(Function base, Function power) {
        this.base = base;
        this.power = power;
    }

    @Override
    public double getLeftDomainBorder() {
        return power.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder() {
        return power.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x) {
        return Math.pow(base.getFunctionValue(x), power.getFunctionValue(x));
    }
}
