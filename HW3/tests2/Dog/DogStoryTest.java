package tests.Dog;

import org.junit.Assert;

import Solution.Given;
import Solution.Then;
import Solution.When;

public class DogStoryTest {
	protected tests.Dog.Dog dog;
	@Given("a Dog of age &age")
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

	@Then("the house condition is &condition and dog age is &dogAge")
	private void theHouseCondition(String condition, Integer dogAge) {
		Assert.assertEquals(condition, dog.houseCondition());
		Assert.assertEquals(dogAge.toString(), Integer.valueOf(dog.getDogAge()).toString());
		Assert.assertEquals(dogAge.toString(), Integer.valueOf(dog.getDogAge() + 1).toString());
	}
}
