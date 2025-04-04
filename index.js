const ProductRoutes = require("./routes/products.routers"); 
const { AppDataSource } = require("./data/source");
const express = require("express");
const cors = require("cors");

const PORT = 3000;
const app = express();

// Middlewares
app.use(express.json());
app.use(cors());

// Rutas
app.use("/api/v1", ProductRoutes);

// Conectar a la base de datos y levantar el servidor
AppDataSource.initialize().then(() => {
    console.log("Conectado a la base de datos");
    app.listen(PORT, () => console.log(`Servidor corriendo en http://localhost:${PORT}`));
}).catch((err) => {
    console.error("Error al conectar a la base de datos", err);
});
