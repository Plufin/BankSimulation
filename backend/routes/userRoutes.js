var express = require("express");
var router = express.Router();
const userController = require("../controllers/userController");

router.get("/", userController.getAll);
router.post("/", userController.createUser);
router.delete("/:user_id", userController.deleteUser);
router.put("/:user_id", userController.updateUser);

router.get("/:user_id", userController.getById);

module.exports = router;
