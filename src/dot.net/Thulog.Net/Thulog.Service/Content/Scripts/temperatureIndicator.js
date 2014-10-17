var chart1; // globally available
$(function () {
    var serviceUrlLastData = 'http://localhost:50546/api/indicators/GetAllTemperatureData';
    $.getJSON(serviceUrlLastData)
        .done(function (result) {
            var arr = new Array();
            debugger;
            $.each(result, function (key, item) {
                arr.push([Date.parse(item.DateTime), item.Value]);
            });
            chart1 = new Highcharts.StockChart({
                chart: {
                    renderTo: 'temperature_chart_div'
                },
                title: {
                    text: 'Temperature indicator'
                },
                rangeSelector: {
                    selected: 1,
                    inputEnabled: $('#temperature_chart_div').width() > 480
                },
                series: [
                    {
                        name: 'Temperature',
                        data: arr,
                        tooltip: {
                            valueDecimals: 2
                        }
                    }
                ]
            });
        });
});