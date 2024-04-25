const express = require("express");
const cors = require("cors");

const app = express();

app.use(cors());
app.use(express.json());

let productos = [];

app.post("/productos", (req, res) => {
    const { nombre, precio } = req.body;
    const producto = { nombre, precio };
    productos.push(producto);
    res.status(201).send('Producto registrado exitosamente.');
});

app.get("/productos", (req, res) => {
    res.json(productos);
});

app.post("/total", (req, res) => {
    const total = productos.reduce((acc, producto) => acc + producto.precio, 0);
    res.json({ total });
});

// Manejar solicitudes GET en la misma ruta "/total"
app.get("/total", (req, res) => {
    const total = productos.reduce((acc, producto) => acc + producto.precio, 0);
    res.json({ total });
});


app.listen(3000, () => console.log("Servidor creado en el puerto 3000"));
