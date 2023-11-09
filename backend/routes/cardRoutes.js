var express = require("express");
var router = express.Router();
const cardController = require("../controllers/cardController");

router.get("/", cardController.getAll);
router.post("/", cardController.addCard);
router.delete("/:card_id", cardController.deleteCard);
router.put("/:card_id", cardController.updateCard);

router.post("/login", cardController.login);
router.get("/:card_id", cardController.getById);
module.exports = router;
