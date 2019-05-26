package tests.Dog;

import Solution.Then;
import Solution.When;
import org.junit.Assert;

public class DogStoryTestNoGivenAnnotation {
	protected tests.Dog.Dog dog;

	public void aDog(Integer age) {
		dog = new tests.Dog.Dog(age);
	}
	
	@When("the dog is not taken out for a walk, the number of hours is &hours")
	public void dogNotTakenForAWalk(Integer hours) {
		dog.notTakenForAWalk(hours);
	}
	
	@Then("the house condition is &condition")
	public void theHouseCondition(String condition) {
		Assert.assertEquals(condition, dog.houseCondition());
	}
}
