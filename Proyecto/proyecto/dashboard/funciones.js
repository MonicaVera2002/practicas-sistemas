/* Configuración Firebase */
var firebaseConfig = {
    apiKey: "AIzaSyCJgdtxABuri0w7fhkmxmNfRlTVXGSl-ko",
    authDomain: "visionarios-4015a.firebaseapp.com",
    databaseURL: "https://visionarios-4015a-default-rtdb.firebaseio.com/"
};
firebase.initializeApp(firebaseConfig);

/* Sensores de registro */
const paths = {
    lm35: "lm35",
    mq2: "mq2",
    ruido: "ruido",
    vibracion: "vibracion",
    pir: "pir"
};

/* Graficas */
function crearGrafica(ctx, label, color) {
    return new Chart(ctx, {
        type: "line",
        data: {
            labels: [],
            datasets: [{
                label: label,
                data: [],
                borderWidth: 2,
                borderColor: color,
                fill: false
            }]
        }
    });
}

let graficas = {
    lm35: crearGrafica(
        document.getElementById("lm35").getContext("2d"),
        "Temperatura (°C)", "red"
    ),

    mq2: crearGrafica(
        document.getElementById("mq2").getContext("2d"),
        "Gas", "orange"
    ),

    ruido: crearGrafica(
        document.getElementById("ruido").getContext("2d"),
        "Ruido", "blue"
    ),

    vibracion: crearGrafica(
        document.getElementById("vibracion").getContext("2d"),
        "Vibración", "green"
    ),

    pir: crearGrafica(
        document.getElementById("pir").getContext("2d"),
        "Movimiento", "purple"
    )
};

/* Al mismo tiempo, valores reales*/
function escuchar(path, grafica) {
    firebase.database()
    .ref(path)
    .limitToLast(50)
    .on("child_added", (snap) => {

        let d = snap.val();
        if (!d || d.valor == null) return;

        grafica.data.labels.push("");
        grafica.data.datasets[0].data.push(d.valor);

        if (grafica.data.labels.length > 50) {
            grafica.data.labels.shift();
            grafica.data.datasets[0].data.shift();
        }

        grafica.update();
    });
}

escuchar(paths.lm35, graficas.lm35);
escuchar(paths.mq2, graficas.mq2);
escuchar(paths.ruido, graficas.ruido);
escuchar(paths.vibracion, graficas.vibracion);
escuchar(paths.pir, graficas.pir);


