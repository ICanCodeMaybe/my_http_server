function updateText() {
    // Get the user input
    var userInput = document.getElementById("userInput").value;

    // Update the text in the HTML element
    document.getElementById("displayText").textContent = userInput;


	const xhr = new XMLHttpRequest();
	xhr.open("POST", "192.168.11.10");

	xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");

	const body = JSON.stringify({
  	userId: 1,
 	title: userInput,
  	completed: false
	});

	xhr.onload = () => {
  		if (xhr.readyState == 4 && xhr.status == 201) {
    			console.log(JSON.parse(xhr.responseText));
	 	 } else {
  			console.log(`Error: ${xhr.status}`);
  		}
	};

	xhr.send(body);
}
