var express = require("express");
var router = express.Router();
const accountController = require("../controllers/accountController");
const jwt = require("../config/jwt");

router.get("/", accountController.getAll);
router.post("/", accountController.createAccount);
router.delete("/:account_id", accountController.deleteAccount);
router.put("/:account_id", accountController.updateAccount);

router.get("/balance", jwt.verifyToken, accountController.getBalance);
router.get("/:account_id", accountController.getById);
router.post("/withdraw", jwt.verifyToken, accountController.withdraw);

module.exports = router;
