
const db = require('../db/database');

exports.obtenerProductos = (req, res) => {
  db.all('SELECT * FROM productos', [], (err, rows) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(rows);
  });
};

exports.crearVenta = (req, res) => {
  const { productos } = req.body;

  let total = 0;

  const obtenerPrecios = productos.map(p =>
    new Promise((resolve, reject) => {
      db.get('SELECT precio_venta FROM productos WHERE id = ?', [p.producto_id], (err, row) => {
        if (err) reject(err);
        else resolve(p.cantidad * row.precio_venta);
      });
    })
  );

  Promise.all(obtenerPrecios)
    .then(totales => {
      total = totales.reduce((sum, t) => sum + t, 0);
      const iva = +(total * 0.16).toFixed(2);
      const total_con_iva = +(total + iva).toFixed(2);
      const fecha = new Date().toISOString();

      db.run(\`INSERT INTO ventas (fecha, total, iva, total_con_iva) VALUES (?, ?, ?, ?)\`,
        [fecha, total, iva, total_con_iva],
        function (err) {
          if (err) return res.status(500).json({ error: err.message });

          const ventaId = this.lastID;

          productos.forEach(({ producto_id, cantidad }) => {
            db.run(
              \`INSERT INTO venta_detalle (venta_id, producto_id, cantidad) VALUES (?, ?, ?)\`,
              [ventaId, producto_id, cantidad]
            );

            db.run(
              \`UPDATE productos SET stock_actual = stock_actual - ? WHERE id = ?\`,
              [cantidad, producto_id]
            );
          });

          res.json({ ventaId, total, iva, total_con_iva });
        }
      );
    })
    .catch(err => res.status(500).json({ error: err.message }));
};
