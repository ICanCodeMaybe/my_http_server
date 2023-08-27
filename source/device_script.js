//dont jugde me, its basically frist js script, that i have ever wrote

var devices_json = [];

// Fetching the JSON file
fetch('devices.json')
  .then(response => {
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    return response.json(); // This parses the JSON data in the response
  })
  .then(data => {
    devices_json = data; // Here, 'data' is the parsed JSON

    // You can now access the data inside this block
    if (devices_json.length > 0) {
      console.log(devices_json[0].name);
      console.log(devices_json.length);

      modify(devices_json);
    } else {
      console.log('No data found in devices_json array.');
    }
  })
  .catch(error => {
    console.error('There was a problem with the fetch operation:', error);
  });

function modify(devices){
	const num_of_dev = devices.length
	
	const site_root = document.getElementById("root");

	const dev_div = [];

	const dev_head = [];
	const head_text = [];
	
	const dev_ip = [];
	const ip_text = [];

	const dev_link = [];
	const link_text = [];

	const dev_form = [];
	const form_label = [];
	const form_command_input = [];
	const form_button = [];

	for(let i = 0; i < num_of_dev; i++){
	//------creating---------
		//heading
		dev_div[i] = document.createElement("div");
		dev_head[i] = document.createElement("h2");
		head_text[i] = document.createTextNode(devices[i].name);
		//ip
		dev_ip[i] = document.createElement("p");
		ip_text[i] = document.createTextNode("IP - " + devices[i].ip);
		//command link
		dev_link[i] = document.createElement("a");
		link_text[i] = document.createTextNode("commands");
		dev_link[i].title = "commandsss";
		dev_link[i].href = "commands.html";
		//form
		dev_form[i] = document.createElement("form");
		form_label[i] = document.createElement("label");
		form_label[i].textContent = "Write your command here: ";
		form_label[i].appendChild(dev_link[i]);
		form_command_input[i] = document.createElement("input");
		form_command_input[i].type = "text";
		form_command_input[i].name = "command";
		form_command_input[i].id = "command";
		form_button[i] = document.createElement("input");
		form_button[i].type = "submit";
		form_button[i].value = "Send";

		dev_form[i].addEventListener("submit", function(event) {
			event.preventDefault();

			const in_command = event.target.elements.command.value;
			console.log("Command submitted:", in_command);

			sendToSer(in_command, i);
			});

	//------appending--------
		dev_head[i].appendChild(head_text[i]);
		dev_div[i].appendChild(dev_head[i]);

		dev_ip[i].appendChild(ip_text[i]);
		dev_div[i].appendChild(dev_ip[i]);

		dev_link[i].appendChild(link_text[i]);

		//form
		dev_form[i].appendChild(form_label[i]);
		dev_form[i].appendChild(form_command_input[i]);
		dev_form[i].appendChild(form_button[i]);

		dev_div[i].appendChild(dev_form[i]);
		site_root.appendChild(dev_div[i]);
	}
}

function sendToSer(in_command, i){
	fetch('devices.json', {
		method: 'POST',
		body: in_command,
		headers: {
			'Content-Type': 'text/plain'
		}
	})
	.then(response => { 
		if (!response.ok) {
      			throw new Error('Network response was not ok');
    		}
    			return response.text();
	})
	.then(data => console.log(data))
	.catch(error => console.error("Error: ", error));
}

