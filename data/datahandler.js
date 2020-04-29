var ip = String("http://192.168.4.1");
var pollrate = 3000;

var localinstance = false;
var islive = false;
var retrycount = 0;

var powinterval, volinterval, curinterval;

var powerChart = new Highcharts.Chart({
  chart: {
    renderTo: "chart-power",
  },
  title: { text: "Power Graph" },
  series: [
    {
      showInLegend: false,
      data: [],
    },
  ],
  plotOptions: {
    line: {
      dataLabels: { enabled: true },
    },
    series: { color: "#CC66FF" },
  },
  xAxis: {
    type: "datetime",
    dateTimeLabelFormats: { second: "%H:%M:%S" },
  },
  yAxis: {
    title: { text: "Power (mW)" },
  },
  credits: { enabled: false },
});
var voltageChart = new Highcharts.Chart({
  chart: { renderTo: "chart-voltage" },
  title: { text: "Voltage Graph" },
  series: [
    {
      showInLegend: false,
      data: [],
    },
  ],
  plotOptions: {
    line: {
      dataLabels: { enabled: true },
    },
    series: { color: "#3399FF" },
  },
  xAxis: {
    type: "datetime",
    dateTimeLabelFormats: { second: "%H:%M:%S" },
  },
  yAxis: {
    title: { text: "Voltage (V)" },
  },
  credits: { enabled: false },
});

var currentChart = new Highcharts.Chart({
  chart: { renderTo: "chart-current" },
  title: { text: "Current Graph" },
  series: [
    {
      showInLegend: false,
      data: [],
    },
  ],
  plotOptions: {
    line: {
      dataLabels: { enabled: true },
    },
    series: { color: "#CC0033" },
  },
  xAxis: {
    type: "datetime",
    dateTimeLabelFormats: { second: "%H:%M:%S" },
  },
  yAxis: {
    title: { text: "Current (mA)" },
  },
  credits: { enabled: false },
});

function getPower() {
  var request =  String(localinstance ? ip + "/power" : "/power");
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var x = new Date().getTime(),
        y = parseFloat(this.responseText);
      document.getElementById("powbox").innerHTML =
        String(this.responseText) + "mW";
      if (powerChart.series[0].data.length > 40) {
        powerChart.series[0].addPoint([x, y], true, true, true);
      } else {
        powerChart.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", String(request), true);
  xhttp.send();
}

function getVoltage() {
  var request = String(localinstance ? ip + "/voltage" : "/voltage");
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var x = new Date().getTime(),
        y = parseFloat(this.responseText);
      document.getElementById("volbox").innerHTML =
        String(this.responseText) + "V";
      if (voltageChart.series[0].data.length > 40) {
        voltageChart.series[0].addPoint([x, y], true, true, true);
      } else {
        voltageChart.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", request, true);
  xhttp.send();
}

function getCurrent() {
  var request = String(localinstance ? ip + "/current" : "/current");
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var x = new Date().getTime(),
        y = parseFloat(this.responseText);
      document.getElementById("curbox").innerHTML =
        String(this.responseText) + "mA";
      if (currentChart.series[0].data.length > 40) {
        currentChart.series[0].addPoint([x, y], true, true, true);
      } else {
        currentChart.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", request, true);
  xhttp.send();
}

var checkconnection = setInterval(connectToServer, 2000);

function connectToServer() {
  var request = String(localinstance ? ip + "/check" : "/check");
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (this.responseText == "ACK") {
        if (!islive) {
          console.log("Connection live...");
          document.getElementById("powbox").innerHTML = String(
            "Fetching Data :)"
          );
          document.getElementById("volbox").innerHTML = String(
            "Fetching Data :)"
          );
          document.getElementById("curbox").innerHTML = String(
            "Fetching Data :)"
          );
          retrycount = 0;
          document.getElementById("blinker").classList.remove("blinking-off");
          document.getElementById("blinker").classList.add("blinking-on");
          powinterval = setInterval(getPower, pollrate);
          volinterval = setInterval(getVoltage, pollrate);
          curinterval = setInterval(getCurrent, pollrate);
          islive = true;
        }
      }
    } else if (this.readyState == 4 && this.status == 0) {
      document.getElementById("blinker").classList.remove("blinking-on");
      document.getElementById("blinker").classList.add("blinking-off");
      islive = false;
      if (!localinstance) {
        console.log("Set to external IP: " + ip);
        localinstance = true;
      } else if (localinstance && retrycount < 6) {
        retrycount++;
        console.log("Connection lost. Retrying... " + retrycount);
        document.getElementById("powbox").innerHTML = String(
          "Error\nRetrying..."
        );
        document.getElementById("volbox").innerHTML = String(
          "Error\nRetrying..."
        );
        document.getElementById("curbox").innerHTML = String(
          "Error\nRetrying..."
        );
        clearInterval(powinterval);
        clearInterval(volinterval);
        clearInterval(curinterval);
      } else if (retrycount < 7) {
        document.getElementById("powbox").innerHTML = String(
          "Connection\nError :("
        );
        document.getElementById("volbox").innerHTML = String(
          "Connection\nError :("
        );
        document.getElementById("curbox").innerHTML = String(
          "Connection\nError :("
        );
        document.getElementById("blinker").classList.remove("blinking-on");
        document.getElementById("blinker").classList.add("blinking-off");
        retrycount++;
      } else if (retrycount < 8) {
        console.log("Retry count exceeded. We will keep retrying in the background.");
        alert("Error connecting to webserver!\nRefresh and try again.");
        retrycount++;
      }
    }
  };
  xhr.open("GET", request, true);
  xhr.send();
}

document.getElementById("setcala").addEventListener("click", function () {
  sendCalibration("/setcala");
});

document.getElementById("setcalb").addEventListener("click", function () {
  sendCalibration("/setcalb");
});

document.getElementById("setcalc").addEventListener("click", function () {
  sendCalibration("/setcalc");
});

function startInterval(_interval) {
  intervalId = setInterval(_interval);
}

document.getElementById("setpol").addEventListener("click", function () {
  pollrate = Number(document.getElementById("polinp").value);
  pollrate = pollrate < 1 ? 1000 : pollrate * 1000;
  if (islive) {
    clearInterval(powinterval);
    clearInterval(volinterval);
    clearInterval(curinterval);
    powinterval = setInterval(getPower, pollrate);
    volinterval = setInterval(getVoltage, pollrate);
    curinterval = setInterval(getCurrent, pollrate);
  } else {
    alert("Server not connected.\nCannot set polling rate.");
  }
});

function sendCalibration(calstr) {
  var request = String(localinstance ? "http://192.168.4.1" + calstr : calstr);
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", request, true);
  xhttp.send();
}
