document.addEventListener("DOMContentLoaded", () => {
    const contenedorCards = document.getElementById("contenedor-cards");
    const formulario = document.getElementById("Formulario");
    const nombreInput = document.getElementById("NombreProducto");
    const precioInput = document.getElementById("precioProducto");
    const stockInput = document.getElementById("stockProducto");
    const btnLimpiar = document.getElementById("btn-limpiar");

    let isUpdate = false;
    let id = null;

    // Función para mostrar productos en tarjetas
    const mostrarProductos = (productos) => {
        contenedorCards.innerHTML = "";  // Limpiar antes de agregar nuevos productos
        productos.forEach(producto => {
            const card = document.createElement("div");
            card.classList.add("bg-white", "rounded-xl", "shadow-md", "p-6", "hover:scale-105", "transition");

            card.innerHTML = `
                <h3 class="text-xl font-bold text-emerald-800">${producto.nombre}</h3>
                <p class="text-lg font-semibold text-emerald-500 my-2">$${producto.precio}</p>
                <span class="block text-sm text-gray-500">Stock - ${producto.stock}</span>
                <div class="flex gap-3 mt-4">
                    <button onclick='actualizar(${JSON.stringify(producto)})'
                        class="flex-1 px-3 py-2.5 bg-teal-100 text-teal-700 rounded-md hover:bg-teal-200 transition">
                        <i class="bi bi-pencil-square"></i> Editar
                    </button>
                    <button onclick="eliminar(${producto.id}, this)"
                        class="flex-1 px-3 py-2.5 bg-red-100 text-red-700 rounded-md hover:bg-red-200 transition">
                        <i class="bi bi-trash3"></i> Eliminar
                    </button>
                </div>
            `;

            contenedorCards.appendChild(card);
        });
    };

    // Función para obtener los productos desde la API
    const obtenerProductosApi = async () => {
        const response = await fetch("http://localhost:3000/api/v1");
        if (response.ok) {
            const productos = await response.json();
            mostrarProductos(productos);
        }
    };

    // Función para actualizar un producto (Editar)
    window.actualizar = (producto) => {
        isUpdate = true;
        id = producto.id;
        nombreInput.value = producto.nombre;
        precioInput.value = producto.precio;
        stockInput.value = producto.stock;
    };

    // Función para eliminar un producto
    window.eliminar = async (id, boton) => {
        const response = await fetch(`http://localhost:3000/api/v1/${id}`, {
            method: "DELETE",
            headers: { "Content-Type": "application/json" },
        });

        if (response.status === 204) {
            alert("Producto eliminado correctamente");
            obtenerProductosApi();
        } else {
            alert("Error al eliminar el producto");
        }
    };

    // Función para crear o actualizar un producto
    const crearProducto = async (evt) => {
        evt.preventDefault();
        const nombre = nombreInput.value;
        const precio = precioInput.value;
        const stock = stockInput.value;

        const nuevoProducto = { nombre, precio, stock };

        if (!isUpdate) {
            const response = await fetch("http://localhost:3000/api/v1/", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(nuevoProducto)
            });

            if (response.status === 201) {
                alert("Producto creado");
                formulario.reset();
                obtenerProductosApi();
            } else {
                alert("Error al agregar el producto");
            }
        } else {
            const response = await fetch(`http://localhost:3000/api/v1/${id}`, {
                method: "PATCH",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(nuevoProducto)
            });

            if (response.ok) {
                alert("Producto actualizado");
                formulario.reset();
                isUpdate = false;
                id = null;
                obtenerProductosApi();
            } else {
                alert("Error al actualizar el producto");
            }
        }
    };

    // Limpiar el formulario
    btnLimpiar.addEventListener("click", () => {
        formulario.reset();
        isUpdate = false;
        id = null;
    });

    // Evento para enviar el formulario
    formulario.addEventListener("submit", crearProducto);

    // Obtener productos al cargar la página
    obtenerProductosApi();
});
