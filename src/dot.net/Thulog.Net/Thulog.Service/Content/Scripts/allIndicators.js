var serviceUrl = 'http://localhost:50546/api/indicators';
var serviceUrlLastData = 'http://localhost:50546/api/indicators/GetData';
var humidityChartdata, temperatureChartData;
var optionsHumidity, optionsTemperature;
var chartTitle;

google.load("visualization", "1", { packages: ["corechart"] });

$(function () {
    //Get data for the last month
    getLastDataByParam('2', 'Days');
});

//Humidity chart configuartion
function ConfigHumidityChart() {
    humidityChartdata = new google.visualization.DataTable();
    humidityChartdata.addColumn('string', 'Time'); // Implicit domain label col.
    humidityChartdata.addColumn('number', 'Humidity');

    optionsHumidity = {
        title: 'Humidity',
        hAxis: { title: chartTitle, titleTextStyle: { color: 'red' } },
        legend: { position: 'none' }
    };
};

//Temperature chart configuartion
function ConfigTemperatureChart() {
    temperatureChartData = new google.visualization.DataTable();
    temperatureChartData.addColumn('string', 'Time'); // Implicit domain label col.
    temperatureChartData.addColumn('number', 'Temperature');

    optionsTemperature = {
        title: 'Temperature',
        hAxis: { title: chartTitle, titleTextStyle: { color: 'red' } },
        legend: { position: 'none' }
    };
};

//Set datasource for temperature and humidity charts
function setDataForChart(data) {
    //Humidity chart configuartion
    ConfigHumidityChart();

    //Temperature chart configuartion
    ConfigTemperatureChart();

    // On success, 'data' contains a list of products.
    $.each(data, function (key, item) {
        // Add a list item for the product.
        humidityChartdata.addRows([[item.DateTime.toString(), item.Humidity]]);
        temperatureChartData.addRows([[item.DateTime.toString(), item.Temperature]]);
    });
    resize();
};

//Get data by last : 12 hours, day, week, month, year
function getLastDataByParam(param, title) {
    chartTitle = title;
    var data = {};
    data.param = param;
    $.getJSON(serviceUrlLastData, data)
     .success(function (result) {
         setDataForChart(result);
     });
};

//Get data by specific interval
function getDataByInterval() {
    chartTitle = $('#step_radiogruop input:radio:checked').val();
    var data = {};
    data.startDate = $('#dpd1').data('datepicker').date.toISOString();
    data.endDate = $('#dpd2').data('datepicker').date.toISOString();
    data.step = chartTitle;

    $.getJSON(serviceUrl, data)
     .done(function (result) {
         setDataForChart(result);
     });
};

//Redisign char if window was resized
function resize() {
    var humidityChartDiv = document.getElementById('humidity_chart_div');
    var temperatureChartDiv = document.getElementById('temperature_chart_div');

    if (humidityChartDiv && humidityChartdata) {
        var chart = new google.visualization.LineChart(humidityChartDiv);
        chart.draw(humidityChartdata, optionsHumidity);
    }

    if (temperatureChartDiv && temperatureChartData) {
        var chart = new google.visualization.LineChart(temperatureChartDiv);
        chart.draw(temperatureChartData, optionsTemperature);
    }
}

window.onload = resize();
window.onresize = resize;