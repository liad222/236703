package tests.Nested;

import Solution.When;

public class NestedDerivedLevel3Test extends NestedDerivedLevel2Test {
    @When("level3 add &num")
    private void addNum(Integer num) {
        this.calculator.addNum(num);
    }
}
