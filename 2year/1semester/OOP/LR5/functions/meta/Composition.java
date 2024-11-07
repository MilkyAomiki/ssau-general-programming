package functions.meta;

import functions.Function;

public class Composition implements Function {
    private Function funcLeft;
    private Function funcRight;

    public Composition(Function funcLeft, Function funcRight) {
        this.funcLeft = funcLeft;
        this.funcRight = funcRight;
    }

    @Override
    public double getLeftDomainBorder() {
        return Math.min(funcRight.getLeftDomainBorder(), funcLeft.getLeftDomainBorder());
    }

    @Override
    public double getRightDomainBorder() {
        return Math.min(funcRight.getRightDomainBorder(), funcLeft.getRightDomainBorder());
    }

    @Override
    public double getFunctionValue(double x) {
        return funcLeft.getFunctionValue(funcRight.getFunctionValue(x));
    }

}
