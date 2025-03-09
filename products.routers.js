const {productcontroller, ProductController} = require("../controllers/products.controller");
const router = require('express').Router();

router.get("/",ProductController.getAll);
router.get("/:id",ProductController.getOneByld);
router.post("/,",ProductController.create);
router.patch("/:id",ProductController.update);
router.delete("/:id",ProductController.delete);


module.exports = router;