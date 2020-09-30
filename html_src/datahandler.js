var ip = String("http://192.168.4.1");
var pollrate = 3000;

var localinstance = false;
var islive = false;
var retrycount = 0;

var datainterval;

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
    series: { color: "#C800FF" },
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
    series: { color: "#00B0F0" },
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
    series: { color: "#FF0000" },
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

var chargeChart = new Highcharts.Chart({
  chart: { renderTo: "chart-charge" },
  title: { text: "Charge Graph" },
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
    series: { color: "#00B050" },
  },
  xAxis: {
    type: "datetime",
    dateTimeLabelFormats: { second: "%H:%M:%S" },
  },
  yAxis: {
    title: { text: "Charge (mAh)" },
  },
  credits: { enabled: false },
});

var energyChart = new Highcharts.Chart({
  chart: { renderTo: "chart-energy" },
  title: { text: "Energy Graph" },
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
    series: { color: "#FFC000" },
  },
  xAxis: {
    type: "datetime",
    dateTimeLabelFormats: { second: "%H:%M:%S" },
  },
  yAxis: {
    title: { text: "Energy (mWh)" },
  },
  credits: { enabled: false },
});

function fetchData() {
  var request = String(localinstance ? ip + "/readings" : "/readings");
  var xhttp = new XMLHttpRequest();

  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var data = this.responseText.split(",");
      if (data.length == 6) {
        var x = new Date().getTime();
        var y = parseFloat(data[0]);

        document.getElementById("volbox").innerHTML = String(data[0]) + "V";
        if (voltageChart.series[0].data.length > 40) {
          voltageChart.series[0].addPoint([x, y], true, true, true);
        } else {
          voltageChart.series[0].addPoint([x, y], true, false, true);
        }

        y = parseFloat(data[1]);
        document.getElementById("curbox").innerHTML = String(data[1]) + "mA";
        if (currentChart.series[0].data.length > 40) {
          currentChart.series[0].addPoint([x, y], true, true, true);
        } else {
          currentChart.series[0].addPoint([x, y], true, false, true);
        }

        y = parseFloat(data[2]);
        document.getElementById("powbox").innerHTML = String(data[2]) + "mW";
        if (powerChart.series[0].data.length > 40) {
          powerChart.series[0].addPoint([x, y], true, true, true);
        } else {
          powerChart.series[0].addPoint([x, y], true, false, true);
        }

        y = parseFloat(data[3]);
        document.getElementById("chabox").innerHTML = String(data[3]) + "mAh";
        if (chargeChart.series[0].data.length > 40) {
          chargeChart.series[0].addPoint([x, y], true, true, true);
        } else {
          chargeChart.series[0].addPoint([x, y], true, false, true);
        }

        y = parseFloat(data[4]);
        document.getElementById("enerbox").innerHTML = String(data[4]) + "mWh";
        if (energyChart.series[0].data.length > 40) {
          energyChart.series[0].addPoint([x, y], true, true, true);
        } else {
          energyChart.series[0].addPoint([x, y], true, false, true);
        }
      }
    }
  };
  xhttp.open("GET", String(request), true);
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
          document.getElementById("chabox").innerHTML = String(
            "Fetching Data :)"
          );
          document.getElementById("enerbox").innerHTML = String(
            "Fetching Data :)"
          );
          retrycount = 0;
          document.getElementById("blinker").classList.remove("blinking-off");
          document.getElementById("blinker").classList.add("blinking-on");
          datainterval = setInterval(fetchData, pollrate);
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
        document.getElementById("chabox").innerHTML = String(
          "Error\nRetrying..."
        );
        document.getElementById("enerbox").innerHTML = String(
          "Error\nRetrying..."
        );
        clearInterval(datainterval);
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
        document.getElementById("chabox").innerHTML = String(
          "Connection\nError :("
        );
        document.getElementById("enerbox").innerHTML = String(
          "Connection\nError :("
        );
        document.getElementById("blinker").classList.remove("blinking-on");
        document.getElementById("blinker").classList.add("blinking-off");
        retrycount++;
      } else if (retrycount < 8) {
        console.log(
          "Retry count exceeded. We will keep retrying in the background."
        );
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
    clearInterval(datainterval);
    datainterval = setInterval(fetchData, pollrate);
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
