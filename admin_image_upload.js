const express = require('express');
const multer = require('multer');
const pool = require('./database');
const { verifyToken } = require('./auth');

const router = express.Router();

// Configuración de multer para cargar imágenes
const storage = multer.diskStorage({
    destination: 'public/uploads/',
    filename: (req, file, cb) => {
        cb(null, `${Date.now()}-${file.originalname}`);
    }
});

const upload = multer({ storage: storage });

// Ruta para la carga de productos con imagen
router.post('/upload-product', verifyToken, upload.single('image_url'), async (req, res) => {
    const { name, price, stock } = req.body;
    const imageUrl = req.file ? req.file.filename : null;

    if (!name || isNaN(price) || isNaN(stock) || !imageUrl) {
        return res.status(400).json({ message: 'Todos los campos son obligatorios y deben ser válidos' });
    }

    try {
        await pool.execute(
            `INSERT INTO products (name, price, stock, image_url) VALUES (?, ?, ?, ?)`,
            [name, price, stock, imageUrl]
        );
        res.status(201).json({ message: 'Producto agregado con éxito' });
    } catch (error) {
        console.error('Error al subir producto:', error);
        res.status(500).json({ message: 'Error interno del servidor' });
    }
});

module.exports = router;
