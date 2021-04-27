
void printHeader(EthernetClient client)
{
    /*
        This function sends to the client a standard html5 response header
    */

    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Connection: close"));
    client.println();
    DEBUG_SERVERLN(F("Header sent!"));
}

void printPage(EthernetClient client)
{
    /*
        This function contains all the lines of the HTML code that displays the web server page
    */

    client.println(F("<!-- Header -->"));
    client.println(F("<!DOCTYPE HTML>"));
    client.println(F("<html lang='en'>"));
    client.println(F("<head>"));
    client.println(F("<title>BESTduino parametrization</title>"));
    client.println(F("<!-- CSS style -->"));
    client.println(F("<style>"));
    client.println(F("body {"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0;"));
    client.println(F("font-family: Roboto, helvetica, arial, sans-serif;"));
    client.println(F("line-height: 1.5em;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("background-color: #eff4f9;"));
    client.println(F("}"));
    client.println(F("#grid-page {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: 255px auto;"));
    client.println(F("grid-template-rows: 110px 768px auto;"));
    client.println(F("}"));
    client.println(F("#header {"));
    client.println(F("grid-column: 1 / span 2;"));
    client.println(F("background: #ffffff;"));
    client.println(F("}"));
    client.println(F("#header img {"));
    client.println(F("margin: 0;"));
    client.println(F("padding-top: 10px;"));
    client.println(F("width: 235px;"));
    client.println(F("height: 85px;"));
    client.println(F("float: left;"));
    client.println(F("}"));
    client.println(F("#header h1 {"));
    client.println(F("margin: 0;"));
    client.println(F("position: relative;"));
    client.println(F("top: 50px;"));
    client.println(F("left: 0;"));
    client.println(F("text-align: center;"));
    client.println(F("font-size: xx-large;"));
    client.println(F("}"));
    client.println(F("#nav {"));
    client.println(F("float: left;"));
    client.println(F("background: #ffffff;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("}"));
    client.println(F("#footer {"));
    client.println(F("grid-column: 1 / span 2;"));
    client.println(F("position: fixed;"));
    client.println(F("bottom: 0;"));
    client.println(F("clear: left;"));
    client.println(F("width: 100%;"));
    client.println(F("background: #bfe8f5;"));
    client.println(F("text-align: center;"));
    client.println(F("padding: 4px 0;"));
    client.println(F("}"));
    client.println(F("#content {"));
    client.println(F("float: left;"));
    client.println(F("margin-top: 30px;"));
    client.println(F("margin-left: 30px;"));
    client.println(F("margin-right: 30px;"));
    client.println(F("}"));
    client.println(F(".innertube {"));
    client.println(F("margin: 15px;"));
    client.println(F("/* Padding for content */"));
    client.println(F("margin-top: 0;"));
    client.println(F("}"));
    client.println(F("nav ul {"));
    client.println(F("text-align: center;"));
    client.println(F("list-style-type: none;"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0 30px;"));
    client.println(F("}"));
    client.println(F("nav ul a {"));
    client.println(F("text-align: center;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("text-decoration: none;"));
    client.println(F("font-size: large;"));
    client.println(F("}"));
    client.println(F("nav ul a:hover {"));
    client.println(F("background-color: #0b5c98;"));
    client.println(F("color: #ffffff;"));
    client.println(F("}"));
    client.println(F(".buttons {"));
    client.println(F("column-span: all;"));
    client.println(F("}"));
    client.println(F("#grid_container_statuspage {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: auto;"));
    client.println(F("grid-template-rows: repeat(4, auto);"));
    client.println(F("row-gap: 90px;"));
    client.println(F("}"));
    client.println(F("#grid_container_statuspage h2 {"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#working_mode {"));
    client.println(F("display: grid;"));
    client.println(F("justify-content: center;"));
    client.println(F("}"));
    client.println(F("#working_mode p {"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#grid_container_status {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: repeat(6, auto);"));
    client.println(F("grid-template-rows: repeat(3, auto);"));
    client.println(F("justify-content: space-evenly;"));
    client.println(F("row-gap: 10px;"));
    client.println(F("}"));
    client.println(F("#grid_container_status div {"));
    client.println(F("font-weight: bold;"));
    client.println(F("font-size: small;"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#grid_container_sensors {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: repeat(2, auto);"));
    client.println(F("grid-template-rows: repeat(3, auto);"));
    client.println(F("justify-content: space-evenly;"));
    client.println(F("row-gap: 10px;"));
    client.println(F("}"));
    client.println(F("#restartbutton {"));
    client.println(F("display: grid;"));
    client.println(F("justify-content: center;"));
    client.println(F("}"));
    client.println(F(".dot_green {"));
    client.println(F("height: 25px;"));
    client.println(F("width: 25px;"));
    client.println(F("background-color: green;"));
    client.println(F("border-radius: 50%;"));
    client.println(F("display: inline-block;"));
    client.println(F("}"));
    client.println(F(".dot_red {"));
    client.println(F("height: 25px;"));
    client.println(F("width: 25px;"));
    client.println(F("background-color: red;"));
    client.println(F("border-radius: 50%;"));
    client.println(F("display: inline-block;"));
    client.println(F("}"));
    client.println(F("table.formdata {"));
    client.println(F("table-layout: fixed;"));
    client.println(F("overflow: hidden;"));
    client.println(F("border-collapse: collapse;"));
    client.println(F("width: 100%;"));
    client.println(F("margin: 1em 0 2em 0;"));
    client.println(F("}"));
    client.println(F("table.formdata th,"));
    client.println(F("td {"));
    client.println(F("text-align: center;"));
    client.println(F("border: 1px solid #c4cfda;"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0 5px;"));
    client.println(F("white-space: nowrap;"));
    client.println(F("}"));
    client.println(F("table.formdata th {"));
    client.println(F("background-color: #337dae;"));
    client.println(F("color: #ffffff;"));
    client.println(F("}"));
    client.println(F("table.formdata td {"));
    client.println(F("font-weight: lighter;"));
    client.println(F("background-color: white;"));
    client.println(F("}"));
    client.println(F(".description {"));
    client.println(F("overflow: scroll;"));
    client.println(F("}"));
    client.println(F("/* Scrollbar of descriptions */"));
    client.println(F("/* Dimensions */"));
    client.println(F(".description::-webkit-scrollbar {"));
    client.println(F("width: 0;"));
    client.println(F("height: 5px;"));
    client.println(F("}"));
    client.println(F("/* Track */"));
    client.println(F(".description::-webkit-scrollbar-track {"));
    client.println(F("background: #c8dbf5;"));
    client.println(F("}"));
    client.println(F("/* Handle */"));
    client.println(F(".description::-webkit-scrollbar-thumb {"));
    client.println(F("visibility: hidden;"));
    client.println(F("}"));
    client.println(F("/* Handle on hover */"));
    client.println(F(".description::-webkit-scrollbar-thumb:hover {"));
    client.println(F("visibility: visible;"));
    client.println(F("background: rgba(85, 85, 85, 0.575);"));
    client.println(F("}"));
    client.println(F("table.formdata caption {"));
    client.println(F("font-size: larger;"));
    client.println(F("font-weight: bolder;"));
    client.println(F("padding-bottom: 20px;"));
    client.println(F("}"));
    client.println(F(".codecol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".namecol {"));
    client.println(F("width: 9rem;"));
    client.println(F("}"));
    client.println(F(".namecol2 {"));
    client.println(F("width: 10rem;"));
    client.println(F("}"));
    client.println(F(".valuecol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".valuecol2 {"));
    client.println(F("width: 8rem;"));
    client.println(F("}"));
    client.println(F(".unitcol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".rwcol,"));
    client.println(F(".mincol,"));
    client.println(F(".maxcol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".desccol {"));
    client.println(F("width: 30rem;"));
    client.println(F("}"));
    client.println(F("table.formdata input,"));
    client.println(F("select {"));
    client.println(F("text-align: right;"));
    client.println(F("text-align-last: right;"));
    client.println(F("/* For the select element */"));
    client.println(F("width: 100%;"));
    client.println(F("border-style: none;"));
    client.println(F("}"));
    client.println(F("</style>"));
    client.println(F("<link rel='icon' href='data:,'>"));
    client.println(F("<!-- Javascript global variables and functions -->"));
    client.println(F("<script>"));
    client.println(F("var deviceID = 1;"));
    client.println(F("var localPort = 3000;"));
    client.println(F("var remotePort = 3000 + deviceID;"));
    client.println(F("var addressIP = [192, 168, 1, 20 + deviceID];"));
    client.println(F("var addressMAC = ['DE', 'AD', 'BE', 'EF', 'FE', 'ED'];"));
    client.println(F("var cameraRes;"));
    client.println(F("var flagAlert = 0;"));
    client.println(F("// getValuesFromArduino function. For assigning arduino variables values to the global variables used in javascript and in html -->  "));
    client.println(F("function getValuesFromArduino() {"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("var parsedString, tempSection = [];"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4) {"));
    client.println(F("if (this.status == 200) {"));
    client.println(F("if (this.responseText != null) {"));
    client.println(F("parsedString = this.responseText.split('&');"));
    client.println(F("deviceID = parseInt(parsedString[0].split('=')[1]);"));
    client.println(F("remotePort = 3000 + deviceID;"));
    client.println(F("addressIP = [192, 168, 1, 20 + deviceID];"));
    client.println(F("localPort = parseInt(parsedString[1].split('=')[1]);"));
    client.println(F("for (var i = 0; i < 6; i++) {"));
    client.println(F("addressMAC[i] = parsedString[2].split('=')[1].split(':')[i];"));
    client.println(F("}"));
    client.println(F("document.getElementById('deviceID').value = deviceID;"));
    client.println(F("document.getElementById('deviceID').defaultValue = deviceID;"));
    client.println(F("document.getElementById('addressIP[0]').value = addressIP[0];"));
    client.println(F("document.getElementById('addressIP[0]').defaultValue = addressIP[0];"));
    client.println(F("document.getElementById('addressIP[1]').value = addressIP[1];"));
    client.println(F("document.getElementById('addressIP[1]').defaultValue = addressIP[1];"));
    client.println(F("document.getElementById('addressIP[2]').value = addressIP[2];"));
    client.println(F("document.getElementById('addressIP[2]').defaultValue = addressIP[2];"));
    client.println(F("document.getElementById('addressIP[3]').value = addressIP[3];"));
    client.println(F("document.getElementById('addressIP[3]').defaultValue = addressIP[3];"));
    client.println(F("document.getElementById('addressMAC[0]').value = addressMAC[0];"));
    client.println(F("document.getElementById('addressMAC[0]').defaultValue = addressMAC[0];"));
    client.println(F("document.getElementById('addressMAC[1]').value = addressMAC[1];"));
    client.println(F("document.getElementById('addressMAC[1]').defaultValue = addressMAC[1];"));
    client.println(F("document.getElementById('addressMAC[2]').value = addressMAC[2];"));
    client.println(F("document.getElementById('addressMAC[2]').defaultValue = addressMAC[2];"));
    client.println(F("document.getElementById('addressMAC[3]').value = addressMAC[3];"));
    client.println(F("document.getElementById('addressMAC[3]').defaultValue = addressMAC[3];"));
    client.println(F("document.getElementById('addressMAC[4]').value = addressMAC[4];"));
    client.println(F("document.getElementById('addressMAC[4]').defaultValue = addressMAC[4];"));
    client.println(F("document.getElementById('addressMAC[5]').value = addressMAC[5];"));
    client.println(F("document.getElementById('addressMAC[5]').defaultValue = addressMAC[5];"));
    client.println(F("document.getElementById('localPort').value = localPort;"));
    client.println(F("document.getElementById('localPort').defaultValue = localPort;"));
    client.println(F("document.getElementById('remotePort').value = remotePort;"));
    client.println(F("document.getElementById('remotePort').defaultValue = remotePort;"));
    client.println(F("for (var i = 3; i < parsedString.length; i++) {"));
    client.println(F("tempSection = parsedString[i].split('=');"));
    client.println(F("document.getElementById(tempSection[0]).value = parseInt(tempSection[1]);"));
    client.println(F("document.getElementById(tempSection[0]).defaultValue = parseInt(tempSection[1]);"));
    client.println(F("}"));
    client.println(F("cameraRes = parseFloat(document.getElementById('camRes').value);"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxinitialize', true);"));
    client.println(F("request.send(null);"));
    client.println(F("}"));
    client.println(F("function loadPage() {"));
    client.println(F("getValuesFromArduino();"));
    client.println(F("document.getElementById(\"pages\").innerHTML = document.getElementById(\"deviceStatus\").innerHTML; "));
    client.println(F("}"));
    client.println(F("function parseDeviceID() {"));
    client.println(F("deviceID = parseInt(document.getElementById('deviceID').value);"));
    client.println(F("console.log(+deviceID);"));
    client.println(F("addressIP[3] = 20 + deviceID;"));
    client.println(F("remotePort = 3000 + deviceID;"));
    client.println(F("document.getElementById('addressIP[3]').value = addressIP[3];"));
    client.println(F("document.getElementById('remotePort').value = remotePort;"));
    client.println(F("}"));
    client.println(F("// clicked function. For the confirmation button in network paramenters submittion.   "));
    client.println(F("function clicked(e) {"));
    client.println(F("var changed = false;"));
    client.println(F("var element;"));
    client.println(F("element = document.getElementById('deviceID');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[0]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[1]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[2]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[3]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[4]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[5]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('localPort');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("if (changed) {"));
    client.println(F("if (!confirm('Attention: at least one of the Network Parameters has been changed, the device will be restarted. The webserver will be available at the following address: 192.168.1.' + addressIP[3] + '. Do you confirm?'))"));
    client.println(F("e.preventDefault();"));
    client.println(F("} else"));
    client.println(F("e.preventDefault();"));
    client.println(F("}"));
    client.println(F("// ajaxGet function. For sending parameters without refreshing page. Page is refreshed (or changed to new ip) if arduino needs to restart.  "));
    client.println(F("function ajaxGet(whichOne) {"));
    client.println(F("var data = new URLSearchParams();"));
    client.println(F("console.log('GET request done!');"));
    client.println(F("switch (whichOne) {"));
    client.println(F("case 'network':"));
    client.println(F("console.log('Net parameters sent!');"));
    client.println(F("data.append('deviceID', document.getElementById('deviceID').value);"));
    client.println(F("data.append('addressMAC[0]', document.getElementById('addressMAC[0]').value);"));
    client.println(F("data.append('addressMAC[1]', document.getElementById('addressMAC[1]').value);"));
    client.println(F("data.append('addressMAC[2]', document.getElementById('addressMAC[2]').value);"));
    client.println(F("data.append('addressMAC[3]', document.getElementById('addressMAC[3]').value);"));
    client.println(F("data.append('addressMAC[4]', document.getElementById('addressMAC[4]').value);"));
    client.println(F("data.append('addressMAC[5]', document.getElementById('addressMAC[5]').value);"));
    client.println(F("data.append('localPort', document.getElementById('localPort').value);"));
    client.println(F("break;"));
    client.println(F("case 'encoder':"));
    client.println(F("console.log('Encoder parameters sent!');"));
    client.println(F("if (document.getElementById('encDist').value)"));
    client.println(F("data.append('encDist', document.getElementById('encDist').value);"));
    client.println(F("if (document.getElementById('camRes').value) {"));
    client.println(F("cameraRes = parseFloat(document.getElementById('camRes').value);"));
    client.println(F("data.append('camRes', document.getElementById('camRes').value);"));
    client.println(F("}"));
    client.println(F("if (document.getElementById('patRes').value)"));
    client.println(F("data.append('patRes', document.getElementById('patRes').value);"));
    client.println(F("if (document.getElementById('inFilter').value)"));
    client.println(F("data.append('inFilter', document.getElementById('inFilter').value);"));
    client.println(F("if (document.getElementById('outFilter').value)"));
    client.println(F("data.append('outFilter', document.getElementById('outFilter').value);"));
    client.println(F("if (document.getElementById('tSample').value)"));
    client.println(F("data.append('tSample', document.getElementById('tSample').value);"));
    client.println(F("if (document.getElementById('patCurr').value)"));
    client.println(F("data.append('patCurr', document.getElementById('patCurr').value);"));
    client.println(F("}"));
    client.println(F("var xhr = new XMLHttpRequest();"));
    client.println(F("alert('Parameters updating procedure started. Do not change the parameters while this procedure is running. Thank you :) ');"));
    client.println(F("xhr.open('GET', data.toString());"));
    client.println(F("xhr.onload = function () { console.log(this.response) };"));
    client.println(F("xhr.send();"));
    client.println(F("if (whichOne == 'network') {"));
    client.println(F("refreshPage();"));
    client.println(F("}"));
    client.println(F("return false;"));
    client.println(F("}"));
    client.println(F("// function that refresh the page after 6 seconds.  "));
    client.println(F("function refreshPage() {"));
    client.println(F("setTimeout(function () {"));
    client.println(F("location.replace('http://' + addressIP[0] + '.' + addressIP[1] + '.' + addressIP[2] + '.' + addressIP[3]);"));
    client.println(F("}, 6000);"));
    client.println(F("}"));
    client.println(F("// function that is called every 5s to get from the arduino the diagnostic of the device  "));
    client.println(F("window.setInterval(function () {"));
    client.println(F("nocache = '&nocache=' + Math.random() * 10;"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("var status, errors, SPIsendParametersStatus;"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4 &&"));
    client.println(F("this.status == 200 &&"));
    client.println(F("this.responseText != null) {"));
    client.println(F("statusArray = this.responseText.split('&');"));
    client.println(F("workingMode = parseInt(statusArray[0].split('=')[1]);"));
    client.println(F("(workingMode) ? document.getElementById('working_mode_text').innerHTML = '<p>Encoder Mode</p>' : document.getElementById('working_mode_text').innerHTML = '<p>Idle Mode</p>';"));
    client.println(F("errors = parseInt(statusArray[1].split('=')[1]);"));
    client.println(F("((errors >> 7) & 0x01) ? document.getElementById('sensLED').className = 'dot_green' : document.getElementById('sensLED').className = 'dot_red';"));
    client.println(F("((errors >> 6) & 0x01) ? document.getElementById('stmhLED').className = 'dot_green' : document.getElementById('stmhLED').className = 'dot_red';"));
    client.println(F("((errors >> 5) & 0x01) ? document.getElementById('spiLED').className = 'dot_green' : document.getElementById('spiLED').className = 'dot_red';"));
    client.println(F("((errors >> 3) & 0x01) ? document.getElementById('pwrLED').className = 'dot_green' : document.getElementById('pwrLED').className = 'dot_red';"));
    client.println(F("((errors >> 2) & 0x01) ? document.getElementById('tempLED').className = 'dot_green' : document.getElementById('tempLED').className = 'dot_red';"));
    client.println(F("((errors >> 1) & 0x01) ? document.getElementById('stmsLED').className = 'dot_green' : document.getElementById('stmsLED').className = 'dot_red';"));
    client.println(F("document.getElementById('tempValue').innerHTML = \"Temperature: \" + statusArray[3].split('=')[1] "));
    client.println(F("document.getElementById('humValue').innerHTML = \"Humidity: \" + statusArray[4].split('=')[1] "));
    client.println(F("document.getElementById('axisX').innerHTML = \"X-Axis: \" + statusArray[5].split('=')[1] "));
    client.println(F("document.getElementById('axisY').innerHTML = \"Y-Axis: \" + statusArray[6].split('=')[1] "));
    client.println(F("document.getElementById('barPressure').innerHTML = \"Pressure: \" + statusArray[7].split('=')[1] "));
    client.println(F("SPIsendParametersStatus = parseInt(statusArray[2].split('=')[1]);"));
    client.println(F("if (SPIsendParametersStatus == 0 && flagAlert == 1) {"));
    client.println(F("alert('Parameters updated succesfully');"));
    client.println(F("flagAlert = 0;"));
    client.println(F("}"));
    client.println(F("else if (SPIsendParametersStatus > 0 && flagAlert == 1) {"));
    client.println(F("alert(' Error in SPI sending parameters. Probably the SPI bus is broken.'); flagAlert = 0;"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxupdatediag' + nocache, true);"));
    client.println(F("request.send(null);"));
    client.println(F("}, 400);"));
    client.println(F("// function that manages the shifting between pages. It needs to request variables' values from arduino.  "));
    client.println(F("function updateForm(whichOne) {"));
    client.println(F("getValuesFromArduino();"));
    client.println(F("document.getElementById(\"pages\").innerHTML = document.getElementById(whichOne).innerHTML; "));
    client.println(F("return false;"));
    client.println(F("}"));
    client.println(F("// function that populates the equivalent encoder resolution field in the resolution page  "));
    client.println(F("function estimateResolution() {"));
    client.println(F("var rollRad = parseFloat(document.getElementById('rollRad').value);"));
    client.println(F("var leaThick = parseFloat(document.getElementById('leaThick').value);"));
    client.println(F("document.getElementById('encRes').value = (2 * Math.PI * (rollRad + leaThick) / cameraRes * 1000).toFixed(2);"));
    client.println(F("}"));
    client.println(F("// function that sends a reset request to the arduino. It refreshes the page when the server responds.  "));
    client.println(F("function ajaxSendReset() {"));
    client.println(F("if (confirm('Device will be restarted. Are you sure?')) {"));
    client.println(F("console.log('Reset Requested');"));
    client.println(F("nocache = '&nocache=' + Math.random() * 10;"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4) {"));
    client.println(F("if (this.status == 200) {"));
    client.println(F("if (this.responseText != null) {"));
    client.println(F("refreshPage();"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxreset' + nocache, true);"));
    client.println(F("request.send(null);"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("// Header end"));
    client.println(F("</script>"));
    client.println(F("</head>"));
    client.println(F("<!-- Body -->"));
    client.println(F("<body onload='loadPage()'>"));
    client.println(F("<div id='grid-page'>"));
    client.println(F("<header id='header'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<a href=''>"));
    client.println(F("<img src='https://www.brevetti-cea.com/templates/yootheme/cache/Brevetti_CEA_Logo-a2f21874.png'"));
    client.println(F("alt='Brevetti CEA Logo' style='width:400;height:151;'>"));
    client.println(F("</a>"));
    client.println(F("<!--<h1>Brevetti CEA</h1> -->"));
    client.println(F("<h1>BESTduino encoder</h1>"));
    client.println(F("</div>"));
    client.println(F("</header>"));
    client.println(F("<!--<div id='wrapper'>-->"));
    client.println(F("<!-- Navigation side bar -->"));
    client.println(F("<nav id='nav'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<h2 style='text-align: center;'>Menu</h2>"));
    client.println(F("<br>"));
    client.println(F("<ul>"));
    client.println(F("<li><a id='statusLink' title='Click to show device status' href='#'"));
    client.println(F("onclick='updateForm(\"deviceStatus\");'>Encoder status</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='netParamLink' title='Click to show network parameters' href='#'"));
    client.println(F("onclick='updateForm(\"networkParams\");'>Network parameters</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='encParamLink' title='Click to show sensor parameters' href='#'"));
    client.println(F("onclick='updateForm(\"encoderParams\");'>Encoder parameters</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='resEstimationLink' title='Click to show resolution estimation page' href='#'"));
    client.println(F("onclick='updateForm(\"resEstimation\");'>Estimated resolution</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='resOeirnetationLink' title='Click to show oriantation page' href='#'"));
    client.println(F("onclick='updateForm(\"resOrientation\");'>Encoder positioning</a>"));
    client.println(F("</li>"));
    client.println(F("</ul>"));
    client.println(F("</div>"));
    client.println(F("</nav>"));
    client.println(F("<!-- Main content -->"));
    client.println(F("<main id='content'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<div id='pages'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</main>")); //todo  cancel commented lines---------------------------------------
    /*
    client.println(F("<!-- </div> -->"));
    client.println(F("<!-- Footer -->"));
    client.println(F("<footer id='footer'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("</div>"));
    client.println(F("</footer>"));
    */
    client.println(F("</div>")); //todo up to this point ---------------------------------------
    client.println(F("<div id='deviceStatus' style='display: none;'>"));
    client.println(F("<div id='grid_container_statuspage'>"));
    client.println(F("<div id='working_mode'>"));
    client.println(F("<h2>Working Mode</h2>"));
    client.println(F("<div id='working_mode_text'></div>"));
    client.println(F("</div>"));
    client.println(F("<div id='grid_container_sensors'>"));
    client.println(F("<h2 style='grid-column:1 / span 3;'>Ambient sensors</h2>"));
    client.println(F("<p id='tempValue'>Internal temperature</p>"));
    client.println(F("<p id='humValue'>Relative humidity</p>"));
    client.println(F("<p id='barPressure'>Barometric pressure</p>"));
    client.println(F("</div>"));
    client.println(F("<div id='grid_container_status'>"));
    client.println(F("<h2 style='grid-column:1 / span 6;'>Errors</h2>"));
    client.println(F("<div>Main sensor</div>"));
    client.println(F("<div>STM Hardware</div>"));
    client.println(F("<div>SPI Communication</div>"));
    client.println(F("<div>Power Supply</div>"));
    client.println(F("<div>Overheating</div>"));
    client.println(F("<div>STM Software Time</div>"));
    client.println(F("<div><span id='sensLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='stmhLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='spiLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='pwrLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='tempLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='stmsLED' class='dot_red'></span></div>"));
    client.println(F("</div>"));
    client.println(F("<div style='display:grid; justify-content: center;'>"));
    client.println(F("<input type='button' onclick='ajaxSendReset()' value='Restart Device'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("<!-- Forms (initially hidden, shown via javascript) -->"));
    client.println(F("<!-- Form for network parameters -->"));
    client.println(F("<div id='networkParams' style='display: none;'>"));
    client.println(F("<form method='get' onsubmit='return ajaxGet(\"network\")'>"));
    client.println(F("<table class='formdata' summary='This table contains a form for saving network parameters'>"));
    client.println(F("<caption>Network Parameters</caption>"));
    client.println(F("<colgroup>"));
    client.println(F("<col class='codecol'>"));
    client.println(F("<col class='namecol'>"));
    client.println(F("<col class='valuecol'>"));
    client.println(F("<col class='rwcol'>"));
    client.println(F("<col class='mincol'>"));
    client.println(F("<col class='maxcol'>"));
    client.println(F("<col class='desccol'>"));
    client.println(F("</colgroup>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='col'>Code</th>"));
    client.println(F("<th scope='col'>Name</th>"));
    client.println(F("<th scope='col'>Value</th>"));
    client.println(F("<th scope='col'>R/W</th>"));
    client.println(F("<th scope='col'>Min</th>"));
    client.println(F("<th scope='col'>Max</th>"));
    client.println(F("<th scope='col'>Description</th>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p01</th>"));
    client.println(F("<td style='text-align: left;'>Device Index</td>"));
    client.println(F("<td><input type=' number' oninput='parseDeviceID()' name='deviceID' id='deviceID' min='1' max='235'"));
    client.println(F("required></td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>1</td>"));
    client.println(F("<td>235</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Progressive index of the device. Make sure that each "));
    client.println(F("device in a net has a<br>"));
    client.println(F("univoque ID. This parameter directly sets the IP Address of the device and<br>the remote port to"));
    client.println(F("which it sends UDP data</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[0]</th>"));
    client.println(F("<td rowspan='4' style='text-align: left;'>IP Address</td>"));
    client.println(F("<td><input type='text' name='addressIP[0]' id='addressIP[0]' size='3' readonly></td>"));
    client.println(F("<td rowspan='4'>R</td>"));
    client.println(F("<td rowspan='4'></td>"));
    client.println(F("<td rowspan='4'></td>"));
    client.println(F("<td class='description' rowspan='4' style='text-align: left;'>IP Address for the ethernet interface of "));
    client.println(F("the device; p02[0] to"));
    client.println(F("p02[2] are fixed<br> while P02[3] is computed as: 20 + p01</td>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[1]</th>"));
    client.println(F("<td><input type='text' name='addressIP[1]' id='addressIP[1]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[2]</th>"));
    client.println(F("<td><input type='text' name='addressIP[2]' id='addressIP[2]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[3]</th>"));
    client.println(F("<td><input type='text' name='addressIP[3]' id='addressIP[3]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[0]</th>"));
    client.println(F("<td rowspan='6' style='text-align: left;'>MAC Address</td>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F)'"));
    client.println(F("id='addressMAC[0]' name='addressMAC[0]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("<td rowspan='6'>RW</td>"));
    client.println(F("<td rowspan='6'>00</td>"));
    client.println(F("<td rowspan='6'>FF</td>"));
    client.println(F("<td class='description' rowspan='6' style='text-align: left;'>MAC Address for the ethernet"));
    client.println(F("interface of the device. When there is more<br> than one device are present in the same subnet, "));
    client.println(F("make sure that each one<br> has a unique MAC address</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[1]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[1]' name='addressMAC[1]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[2]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[2]' name='addressMAC[2]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[3]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[3]' name='addressMAC[3]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[4]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[4]' name='addressMAC[4]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[5]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[5]' name='addressMAC[5]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p04</th>"));
    client.println(F("<td style='text-align: left;'>Local UDP Port</td>"));
    client.println(F("<td><input type=' number' name='localPort' id='localPort' min='3000' max='4000' required></td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>3000</td>"));
    client.println(F("<td>4000</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Local port that receives UDP data.</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p05</th>"));
    client.println(F("<td style='text-align: left;'>Remote UDP Port</td>"));
    client.println(F("<td><input type=' number' id='remotePort' name='remotePort' readonly></td>"));
    client.println(F("<td>R</td>"));
    client.println(F("<td></td>"));
    client.println(F("<td></td>"));
    client.println(F("<td class='description' style='text-align: left;'>Remote port to which the device sends UDP data."));
    client.println(F("It is computed as: 3000<br> + p01</td>"));
    client.println(F("</tr>"));
    client.println(F("</table>"));
    client.println(F("<!-- Buttons -->"));
    client.println(F("<div class='buttons'>"));
    client.println(F("<input type='reset' name='resetNetworkParams'>"));
    client.println(F("<input type='submit' name='submitNetworkParams' onclick='clicked(event)'>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder parameters -->"));
    client.println(F("<div id='encoderParams' style='display: none;'>"));
    client.println(F("<form method='get' onsubmit='return ajaxGet(\"encoder\")'>"));
    client.println(F("<table class='formdata' summary='This table contains a form for saving encoder parameters'>"));
    client.println(F("<caption>Encoder parameters</caption>"));
    client.println(F("<colgroup>"));
    client.println(F("<col class='codecol'>"));
    client.println(F("<col class='namecol2'>"));
    client.println(F("<col class='valuecol2'>"));
    client.println(F("<col class='unitcol'>"));
    client.println(F("<col class='rwcol'>"));
    client.println(F("<col class='mincol'>"));
    client.println(F("<col class='maxcol'>"));
    client.println(F("<col class='desccol'>"));
    client.println(F("</colgroup>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='col'>Code</th>"));
    client.println(F("<th scope='col'>Name</th>"));
    client.println(F("<th scope='col'>Value</th>"));
    client.println(F("<th scope='col'>Unit</th>"));
    client.println(F("<th scope='col'>R/W</th>"));
    client.println(F("<th scope='col'>Min</th>"));
    client.println(F("<th scope='col'>Max</th>"));
    client.println(F("<th scope='col'>Description</th>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p21</th>"));
    client.println(F("<td style='text-align: left;'>Measuring distance</td>"));
    client.println(F("<td><input type='number' name='encDist' id='encDist' min='15' max='35'></td>"));
    client.println(F("<td>mm</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>15</td>"));
    client.println(F("<td>35</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Distance between the reading face of the sensor and the tracked"));
    client.println(F("<br>surface</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p22</th>"));
    client.println(F("<td style='text-align: left;'>Tracking resolution</td>"));
    client.println(F("<td><input type='number' name='camRes' id='camRes' min='30' max='50'></td>"));
    client.println(F("<td>um</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>30</td>"));
    client.println(F("<td>50</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Minimun tracking resolution of the inspection system</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p23</th>"));
    client.println(F("<td style='text-align: left;'>Sensor resolution</td>"));
    client.println(F("<td><input type='number' name='patRes' id='patRes' min='1000' max='4000'></td>"));
    client.println(F("<td>cpi</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>1000</td>"));
    client.println(F("<td>4000</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Counts per inch of the main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p24</th>"));
    client.println(F("<td style='text-align: left;'>Encoder input filter</td>"));
    client.println(F("<td><input type='number' name='inFilter' id='inFilter' min='5' max='40'></td>"));
    client.println(F("<td>samples</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>5</td>"));
    client.println(F("<td>40</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Number of samples composing the window of the moving"));
    client.println(F("average<br> filter applied to the measure of the main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p25</th>"));
    client.println(F("<td style='text-align: left;'>Encoder output filter</td>"));
    client.println(F("<td><input type='number' name='outFilter' id='outFilter' min='2' max='40'></td>"));
    client.println(F("<td>samples</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>2</td>"));
    client.println(F("<td>40</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Number of samples composing the window of the moving"));
    client.println(F("average<br> filter applied to the output frequency signal</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p26</th>"));
    client.println(F("<td style='text-align: left;'>Sampling Period</td>"));
    client.println(F("<td><input type='number' name='tSample' id='tSample' min='350' max='1300'></td>"));
    client.println(F("<td>us</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>350</td>"));
    client.println(F("<td>1300</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Time between consecutive samples of the main sensor"));
    client.println(F("measure</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p27</th>"));
    client.println(F("<td style='text-align: left;'>Main Sensor Current</td>"));
    client.println(F("<td><select class='input' name='patCurr' id='patCurr'>"));
    client.println(F("<option value='5'>0x05 (6.0mA)</option>"));
    client.println(F("<option value='6'>0x06 (7.2mA)</option>"));
    client.println(F("</select></td>"));
    client.println(F("<td>mA</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>0x05</td>"));
    client.println(F("<td>0x06</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Maximun current for main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("</table>"));
    client.println(F("<!-- Buttons -->"));
    client.println(F("<div class='buttons'>"));
    client.println(F("<input type='reset' name='resetEncoderParams'>"));
    client.println(F("<input type='submit' name='submitEncoderParams'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder resolution estimation -->"));
    client.println(F("<div id='resEstimation' style='display:none'>"));
    client.println(F("<form>"));
    client.println(F("<!-- Roller radius -->"));
    client.println(F("<div>"));
    client.println(F("<label for='rollRad'>Roller radius:</label><br>"));
    client.println(F("<input type='number' name='rollRad' id='rollRad' oninput='estimateResolution()' min='0'> mm"));
    client.println(F("</div>"));
    client.println(F("<!-- Leather thickness -->"));
    client.println(F("<div>"));
    client.println(F("<label for='leaThick'>Leather thickness:</label><br>"));
    client.println(F("<input type='number' name='leaThick' id='leaThick' oninput='estimateResolution()' min='0'> mm"));
    client.println(F("</div>"));
    client.println(F("<!-- Encoder resolution -->"));
    client.println(F("<div>"));
    client.println(F("<label for='encRes'>Equivalent Rotary Encoder Resolution:</label><br>"));
    client.println(F("<input type='number' name='encRes' id='encRes' readonly> ppr"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder orientation Panel --> //TODO orientaZIONE DA FINIRE"));
    client.println(F("<div id='resOrientation' style='display:none'>"));
    client.println(F("<div>    "));
    client.println(F("<h2 style='grid-column:1 / span 2;'>Sensors</h2> "));
    client.println(F("<p id='axisX'> Axis X</p> "));
    client.println(F("<p id='axisY'>Axis Y</p> "));
    client.println(F("</div> "));
    client.println(F("</div>"));
    client.println(F("</body>"));
    client.println(F("</html>"));
}

unsigned char h2d(unsigned char hex_1, unsigned char hex_2)
{
    /*
        This function takes two characters and outputs a char that meets the formatting of a byte in HEX
    */

    unsigned char temp1, temp2;

    if (hex_1 > 0x39)
        hex_1 -= 7; // adjust for hex letters upper or lower case
    temp1 = hex_1 & 0xf;

    if (hex_2 > 0x39)
        hex_2 -= 7; // adjust for hex letters upper or lower case
    temp2 = hex_2 & 0xf;

    return ((temp1 << 4) | temp2);
}

String findData(int from)
{
    /*
        This function returns a substring of the HTTP request "webGetString" that is contained between a
        '&' and a '=', starting from the index "from"
    */

    boolean finish = false;
    boolean reading = false;
    int i = from;
    String parsedData;

    while (!finish)
    {
        if ((webGetString[i] == '&') || (webGetString[i] == ' '))
        {
            finish = true;
            return parsedData;
        }
        if (reading)
        {
            parsedData += webGetString[i];
            DEBUG_SERVERLN(parsedData);
        }
        if (webGetString[i] == '=')
        {
            reading = true;
        }
        i++;
    }
}

int parseResponse()
{
    /*
        This function extracts from the HTTP request of the client (submit method='GET') all the relevant
        parameters and stores them in the EEPROM. If some network parameters have been changed, the function
        returns 'true', otherwise it returns 'false'
    */

    bool restartNeeded = false;
    bool transmissionNeeded = false;
    int tempIndex;
    String tempData;

    tempIndex = webGetString.indexOf("deviceID");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (tempData.toInt() != encPoint->deviceIndex)
        {
            encPoint->deviceIndex = tempData.toInt();
            DEBUG_SERVER(F("New Device ID is: "));
            DEBUG_SERVERLN(encPoint->deviceIndex);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_DEV_INDX, encPoint->deviceIndex); // save parameters on EEPROM
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("devIndex not saved"));
            else
                DEBUG_SERVERLN(F("devIndex saved on EEPROM"));
#endif
            restartNeeded = true; // indicate that encoder restart is needed
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B0 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (h2d(tempData[0], tempData[1]) != encPoint->mac[0])
        {
            encPoint->mac[0] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [0] is: "));
            DEBUG_SERVERLN(encPoint->mac[0]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_ZERO, encPoint->mac[0]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[0] not saved"));
            else
                DEBUG_SERVERLN(F("mac[0] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B1 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (h2d(tempData[0], tempData[1]) != encPoint->mac[1])
        {
            encPoint->mac[1] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [1] is: "));
            DEBUG_SERVERLN(encPoint->mac[1]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_ONE, encPoint->mac[1]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[1] not saved"));
            else
                DEBUG_SERVERLN(F("mac[1] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B2 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (h2d(tempData[0], tempData[1]) != encPoint->mac[2])
        {
            encPoint->mac[2] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [2] is: "));
            DEBUG_SERVERLN(encPoint->mac[2]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_TWO, encPoint->mac[2]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[2] not saved"));
            else
                DEBUG_SERVERLN(F("mac[2] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B3 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (h2d(tempData[0], tempData[1]) != encPoint->mac[3])
        {
            encPoint->mac[3] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [3] is: "));
            DEBUG_SERVERLN(encPoint->mac[3]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_THREE, encPoint->mac[3]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[3] not saved"));
            else
                DEBUG_SERVERLN(F("mac[3] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B4 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (h2d(tempData[0], tempData[1]) != encPoint->mac[4])
        {
            encPoint->mac[4] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [4] is: "));
            DEBUG_SERVERLN(encPoint->mac[4]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_FOUR, encPoint->mac[4]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[4] not saved"));
            else
                DEBUG_SERVERLN(F("mac[4] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B5 % 5D");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);

        if (h2d(tempData[0], tempData[1]) != encPoint->mac[5])
        {
            encPoint->mac[5] = h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [5] is: "));
            DEBUG_SERVERLN(encPoint->mac[5]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadBI2C(LOCATION_MAC_FIVE, encPoint->mac[5]);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[5] not saved"));
            else
                DEBUG_SERVERLN(F("mac[5] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("localPort");
    if (tempIndex >= 0)
    {
        tempData = findData(tempIndex);
        if (tempData.toInt() != encPoint->localPort)
        {
            encPoint->localPort = tempData.toInt();
            DEBUG_SERVER(F("New Local Port is: "));
            DEBUG_SERVERLN(encPoint->localPort);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = myEncoder.writeReadWI2C(LOCATION_LOCAL_PORT, encPoint->localPort);
            delayMicroseconds(SHORTDELAY_I2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("localPort not saved"));
            else
                DEBUG_SERVERLN(F("localPort saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }
    for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
    {
        tempIndex = webGetString.indexOf(deviceParamNames[i]);
        if (tempIndex >= 0)
        {
            tempData = findData(tempIndex);
            if (tempData.toInt() != encPoint->deviceParameters[i])
            {
                encPoint->deviceParameters[i] = tempData.toInt();
                DEBUG_SERVER(F("New "));
                DEBUG_SERVER(deviceParamNames[i]);
                DEBUG_SERVER(F(" is: "));
                DEBUG_SERVERLN(encPoint->deviceParameters[i]);
#ifdef EXTMEMORY_ON
                bool tempFlag;
                tempFlag = myEncoder.writeReadWI2C(LOCATION_DEV_PARAM + 2 * i, encPoint->deviceParameters[i]);
                delayMicroseconds(SHORTDELAY_I2C);
                if (!tempFlag)
                {
                    DEBUG_SERVER(deviceParamNames[i]);
                    DEBUG_SERVERLN(F(" not saved"));
                }
                else
                {
                    DEBUG_SERVER(deviceParamNames[i]);
                    DEBUG_SERVERLN(F(" saved on EEPROM"));
                }
#endif
            }
            transmissionNeeded = true;
        }
    }
    // Return 1 if only restartNeeded, 2 if only transmissionNeeded, 3 if both
    DEBUG_SERVER(F("parseResponse is returning: "));
    DEBUG_SERVERLN(restartNeeded | (transmissionNeeded << 1));
    return (restartNeeded | (transmissionNeeded << 1));
}

void ajaxInitialize(EthernetClient client)
{
    /*
        This functions is a response from the server (Arduino) to a HTTP request of the clients that contains
        the 'ajaxinitialize' string.The server sends to the client a string that contains names and values of
        the parameters. The correct format is Name1=Value1&Name2=Value2&...
    */

    client.print(F("ID ="));
    client.print(encPoint->deviceIndex);
    client.print(F("&"));
    client.print(F("lPort ="));
    client.print(encPoint->localPort);
    client.print(F("&"));
    client.print(F("macAddr ="));
    for (int i = 0; i < 6; i++)
    {
        client.print(encPoint->mac[i], HEX);
        if (i < 5)
            client.print(F(":"));
    }
    client.print(F("&"));
    for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
    {
        client.print(deviceParamNames[i]);
        client.print(F("="));
        client.print(encPoint->deviceParameters[i]);
        if (i < NUMBER_OF_PARAMETERS - 1)
            client.print(F("&"));
    }

#ifdef DEBUG
    DEBUG_SERVERLN(F("Response sent: "));
    DEBUG_SERVER(F("ID = "));
    DEBUG_SERVER(encPoint->deviceIndex);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("lPort = "));
    DEBUG_SERVER(encPoint->localPort);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("macAddr = "));
    for (int i = 0; i < 6; i++)
    {
        DEBUG_SERVERFLO(encPoint->mac[i], HEX);
        if (i < 5)
            DEBUG_SERVER(F(": "));
    }
    DEBUG_SERVER(F("&"));
    for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
    {
        DEBUG_SERVER(deviceParamNames[i]);
        DEBUG_SERVER(F(" = "));
        DEBUG_SERVER(encPoint->deviceParameters[i]);
        if (i < NUMBER_OF_PARAMETERS - 1)
            DEBUG_SERVER(F("&"));
    }
#endif
}

void ajaxUpdateDiag(EthernetClient client)
{
    /*
        This fcn updates the values showed in the webserver. Is a fcn called every 5 seconds.
    */
    cnt_debug++;
    client.print(F("working_mode = "));
    client.print(PLC_STATUS, DEC);
    client.print(F("&"));
    client.print(F("status = "));
    client.print(deviceStatus, DEC);
    client.print(F("&SPIerrorIndex = "));
    client.print(SPIerrorIndex, DEC);
    client.print(F("&tC = "));
    client.print(secPoint->tC, DEC);
    client.print(F("&hP = "));
    client.print(secPoint->hP, DEC);
#if defined(SCREEN_ON) && defined(ACCELEROMETER_ON)
    if (displayScreenNum != 4)
        myEncoder.imuRead();
#elif !defined(SCREEN_ON) && defined(ACCELEROMETER_ON)
    myEncoder.imuRead();
#endif
    client.print(F("&axisX = "));
    client.print(imuPoint->angX, DEC);
    client.print(F("&"));
    client.print(F("axisY = "));
    client.print(imuPoint->angY, DEC);
    client.print(F("&bPre = "));
    client.print(secPoint->bPre, DEC);
    DEBUG_SERVER(F("working_mode = "));
    DEBUG_SERVERFLO(PLC_STATUS, DEC);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("status = "));
    DEBUG_SERVERFLO(deviceStatus, DEC);
    DEBUG_SERVER(F("&SPIerrorIndex = "));
    DEBUG_SERVERFLO(SPIerrorIndex, DEC);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("tC = "));
    DEBUG_SERVERFLO(secPoint->tC, DEC);
    DEBUG_SERVER(F("&hP = "));
    DEBUG_SERVERFLO(secPoint->hP, DEC);
}

bool displayWebServer()
{
    /*
        Function that manages the whole web server
    */

    int tempReturn = 0;
    bool restartNeeded = false;
    bool transmissionNeeded = false;

    EthernetClient client = server.available(); // Listens for new clients

    if (client)
    {
        boolean currentLineIsBlank = true;

        while (client.connected())
        { // While the client is connected and available
            if (client.available())
            {

                char c = client.read();
                if (webGetString.length() < 300)
                    webGetString += c;

                //Serial.write(c);
                if (c == '\n' && currentLineIsBlank)
                {                        // End of a request (HTTP requests end with \n\r)
                    printHeader(client); // Sends the default response header

                    if (webGetString.indexOf("ajaxinitialize") >= 0)
                    {                                            // If the request contains 'ajaxinitialize', calls the ajaxInitialize function
                        DEBUG_SERVERLN(F("Sto facendo l'ajax")); // that sends the parameters to the client
                        ajaxInitialize(client);
                        break;
                    }
                    else if (webGetString.indexOf("ajaxupdatediag") >= 0)
                    { // If the request contains 'ajaxupdatediag', calls ajaxUpdateDiag function
                        DEBUG_SERVERLN(F("Sto mandando diagnostica"));
                        ajaxUpdateDiag(client);
                        break;
                    }

                    else if (webGetString.indexOf("ajaxreset") >= 0)
                    { // If the request contains 'ajaxreset', sets the memory "restartNeeded" that will cause a device reset
                        DEBUG_SERVERLN(F("Reset request received"));
                        client.print(F("Ok"));
                        restartNeeded = true;
                        break;
                    }
                    else
                    { // Otherwise parses the HTTP request to store any saved parameters and shows the page
                        DEBUG_SERVERLN(F("Mostro la pagina"));
                        tempReturn = parseResponse();
                        DEBUG_SERVERLN(F("======================================="));
                        DEBUG_SERVER(F("parseResponse() return is: "));
                        DEBUG_SERVERLN(tempReturn);
                        restartNeeded = (tempReturn & 0x01) | restartNeeded;
                        transmissionNeeded = tempReturn & 0x02;
                        printPage(client);
                        break;
                    }
                }

                if (c == '\n')
                { // End of a line reached
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                { // Line is not ended
                    currentLineIsBlank = false;
                }
            }
        }

        delay(1); // Wait a moment for the page to be displayed

        client.stop();     // Stop the connection
        webGetString = ""; // Empty the HTTP request string
        DEBUG_SERVERLN(F(" - Fatto, Chiusura connessione"));

        delay(2);
        if (restartNeeded)
        { // If a reinitialization of the arduino is needed (any of the network parameters has been changed) calls the software reset function
            restartNeeded = false;
            DEBUG_SERVERLN(F("At least one critical parameter has been changed. The device will restart"));
            //delay (20);
            ST_RESET_LO;
            delayMicroseconds(500);
            ST_RESET_HI;
            delay(1);
            resetFunc();
        }
    }
    return transmissionNeeded;
}

#ifdef ARDUINO_NANO
void resetFunc()
{
    /*
        Function for software reset using nano_33_BLE
    */

    NVIC_SystemReset();
}
#endif
